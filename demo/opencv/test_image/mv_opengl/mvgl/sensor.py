# -*- coding: utf-8 -*-
"""感測器模擬：理想線性 RGB -> Bayer RAW（含雜訊、黑電平、位元深度）。

用途：給 ISP / 去馬賽克 / 白平衡 / 壞點校正 演算法提供可重現的測試輸入。
"""
import json
import os

import numpy as np

CFA_PATTERNS = {
    # (dy, dx) -> 通道索引 0=R 1=G 2=B
    "RGGB": ((0, 0), (0, 1), (1, 0), (1, 1)),
    "BGGR": None,  # 由 RGGB 推導
    "GRBG": None,
    "GBRG": None,
}


def cfa_layout(cfa="RGGB"):
    """回傳 2x2 陣列，元素為通道索引 (R=0,G=1,B=2)。"""
    base = np.array([[0, 1], [1, 2]], dtype=np.int8)  # RGGB
    cfa = cfa.upper()
    if cfa == "RGGB":
        return base
    if cfa == "BGGR":
        return base[::-1, ::-1].copy()
    if cfa == "GRBG":
        return np.array([[1, 0], [2, 1]], dtype=np.int8)
    if cfa == "GBRG":
        return np.array([[1, 2], [0, 1]], dtype=np.int8)
    raise ValueError("未知 CFA 排列: %s" % cfa)


def mosaic(rgb_linear, cfa="RGGB"):
    """(H,W,3) -> (H,W) 單通道馬賽克。"""
    lay = cfa_layout(cfa)
    H, W = rgb_linear.shape[:2]
    out = np.empty((H, W), dtype=np.float32)
    for dy in range(2):
        for dx in range(2):
            ch = lay[dy, dx]
            out[dy::2, dx::2] = rgb_linear[dy::2, dx::2, ch]
    return out


def add_vignetting(img, strength=0.35, power=2.0):
    """鏡頭暗角（cos^4 近似）。"""
    H, W = img.shape[:2]
    yy, xx = np.mgrid[0:H, 0:W].astype(np.float32)
    cx, cy = (W - 1) / 2.0, (H - 1) / 2.0
    r = np.sqrt(((xx - cx) / cx) ** 2 + ((yy - cy) / cy) ** 2) / np.sqrt(2.0)
    mask = 1.0 - strength * r ** power
    return img * mask[..., None]


def simulate_raw(rgb_linear,
                 cfa="RGGB",
                 wb_gains=(1.0, 1.0, 1.0),
                 exposure=1.0,
                 bit_depth=12,
                 black_level=64,
                 full_well_e=12000.0,
                 read_noise_e=2.0,
                 shot_noise=True,
                 vignetting=0.0,
                 seed=0):
    """回傳 (raw_uint16, meta_dict)。"""
    rng = np.random.default_rng(seed)
    x = np.asarray(rgb_linear, dtype=np.float32) * float(exposure)
    x = x * np.asarray(wb_gains, dtype=np.float32)
    if vignetting > 0:
        x = add_vignetting(np.clip(x, 0.0, 1.0), vignetting)
    x = np.clip(x, 0.0, 1.0)

    mos = mosaic(x, cfa)

    white_level = (1 << bit_depth) - 1
    signal_e = mos.astype(np.float64) * full_well_e
    if shot_noise:
        signal_e = signal_e + rng.normal(0.0, 1.0, signal_e.shape) * np.sqrt(np.maximum(signal_e, 0.0))
    if read_noise_e > 0:
        signal_e = signal_e + rng.normal(0.0, read_noise_e, signal_e.shape)

    code = signal_e / full_well_e * (white_level - black_level) + black_level
    code = np.clip(np.round(code), 0, white_level).astype(np.uint16)

    meta = {
        "width": int(mos.shape[1]),
        "height": int(mos.shape[0]),
        "bit_depth": int(bit_depth),
        "container": "uint16 little-endian",
        "black_level": int(black_level),
        "white_level": int(white_level),
        "cfa": cfa.upper(),
        "wb_gains": [float(g) for g in wb_gains],
        "full_well_e": float(full_well_e),
        "read_noise_e": float(read_noise_e),
        "shot_noise": bool(shot_noise),
        "vignetting": float(vignetting),
        "seed": int(seed),
    }
    return code, meta


def demosaic(mosaic_img, cfa="RGGB"):
    """極簡雙線性去馬賽克（僅供預覽 / 檢查用，不是量產級 ISP）。"""
    lay = cfa_layout(cfa)
    H, W = mosaic_img.shape
    img = mosaic_img.astype(np.float32)
    out = np.zeros((H, W, 3), dtype=np.float32)
    masks = np.zeros((H, W, 3), dtype=bool)
    for dy in range(2):
        for dx in range(2):
            ch = lay[dy, dx]
            masks[dy::2, dx::2, ch] = True

    for ch in range(3):
        m = masks[:, :, ch].astype(np.float32)
        v = np.where(masks[:, :, ch], img, 0.0)
        # 3x3 可分離盒式濾波（歸一化到實際樣本數）
        k = np.array([1.0, 2.0, 1.0], dtype=np.float32)
        den = m.copy()
        num = v.copy()
        for axis in (0, 1):
            num = _conv1d(num, k, axis)
            den = _conv1d(den, k, axis)
        out[:, :, ch] = num / np.maximum(den, 1e-6)
    return np.clip(out, 0.0, 1.0)


def _conv1d(a, k, axis):
    pad = len(k) // 2
    a = np.moveaxis(a, axis, 0)
    ap = np.pad(a, ((pad, pad), (0, 0)) if a.ndim == 2 else ((pad, pad),), mode="edge")
    out = np.zeros_like(a)
    for i, w in enumerate(k):
        out += w * ap[i:i + a.shape[0]]
    return np.moveaxis(out, 0, axis)


def save_raw(path, raw, meta):
    """存成 .raw（uint16 LE）+ 同名 .json 元資料。"""
    os.makedirs(os.path.dirname(os.path.abspath(path)), exist_ok=True)
    raw.astype("<u2").tofile(path)
    meta_path = os.path.splitext(path)[0] + ".json"
    with open(meta_path, "w", encoding="utf-8") as f:
        json.dump(meta, f, indent=2, ensure_ascii=False)
    return path, meta_path
