# -*- coding: utf-8 -*-
"""生成 Bayer RAW 圖（模擬工業/機器視覺感測器輸出）——OpenGL 渲染 + 感測器建模。

流程：GPU 渲染理想線性場景 → 白平衡增益 → 曝光 → (可選)暗角 →
      貝爾馬賽克 → 光子散粒噪聲 + 讀出噪聲 → 黑電平/位元深度量化 → .raw

輸出：
    *.raw            純二進位 uint16（little-endian，無標頭）
    *.json           元資料（CFA 排列、黑/白電平、位深、WB 增益…）
    *_preview.png    去馬賽克後的預覽（僅供目視，不是 ISP 成品）

範例
----
    python gen_raw.py --target colorchecker --bits 12 --cfa RGGB --wb 2.0 1.0 1.55
    python gen_raw.py --input output/chessboard_10x7_sq120.png --bits 10 --vignette 0.4
"""
import argparse
import os

import numpy as np

import mvgl.targets as T
from mvgl import sensor
from mvgl.color import linear_to_srgb, srgb_to_linear
from mvgl.pngio import write_png


def load_png_linear(path, encode="srgb"):
    from PIL import Image
    im = Image.open(path)
    arr = np.asarray(im)
    if arr.ndim == 2:                       # 灰階
        arr = np.repeat(arr[:, :, None], 3, axis=2)
    arr = arr[:, :, :3].astype(np.float64)
    maxv = 65535.0 if arr.max() > 255 else 255.0
    x = arr / maxv
    if encode == "srgb":
        x = srgb_to_linear(x)
    return x.astype(np.float32)


def render_preset(name, size=None):
    if name == "colorchecker":
        img, _ = T.colorchecker(patch_px=320, ssaa=4)
    elif name == "chessboard":
        img, _ = T.chessboard(cols=10, rows=7, square_px=120, ssaa=4)
    elif name == "siemens":
        img, _ = T.siemens_star(size=1600, spokes=72, ssaa=4)
    elif name == "gray_wedge":
        img, _ = T.gray_wedge(steps=21, patch_w=160, height=400, ssaa=4)
    else:
        raise SystemExit("未知 preset: %s" % name)

    if size:  # 最近鄰縮放到目標感測器解析度
        h, w = size
        yy = (np.arange(h) * img.shape[0] // h).clip(0, img.shape[0] - 1)
        xx = (np.arange(w) * img.shape[1] // w).clip(0, img.shape[1] - 1)
        img = img[yy][:, xx]
    return img


def main():
    ap = argparse.ArgumentParser(description="Bayer RAW 生成器")
    src = ap.add_mutually_exclusive_group(required=True)
    src.add_argument("--input", help="輸入 PNG（sRGB 或 16bit）")
    src.add_argument("--target", choices=["colorchecker", "chessboard", "siemens", "gray_wedge"],
                     help="直接由 GPU 渲染預設場景")
    ap.add_argument("--input-encode", default="srgb", choices=["srgb", "linear"])
    ap.add_argument("--size", type=int, nargs=2, metavar=("W", "H"), help="輸出解析度（裁切/縮放）")
    ap.add_argument("--cfa", default="RGGB", choices=["RGGB", "BGGR", "GRBG", "GBRG"])
    ap.add_argument("--bits", type=int, default=12, choices=[8, 10, 12, 14, 16])
    ap.add_argument("--black", type=int, default=64, help="黑電平（code value）")
    ap.add_argument("--full-well", type=float, default=12000.0, help="滿阱電子數")
    ap.add_argument("--read-noise", type=float, default=2.0, help="讀出噪聲 (e-)")
    ap.add_argument("--no-shot-noise", action="store_true")
    ap.add_argument("--wb", type=float, nargs=3, default=(1.0, 1.0, 1.0), metavar=("R", "G", "B"))
    ap.add_argument("--exposure", type=float, default=1.0)
    ap.add_argument("--vignette", type=float, default=0.0, help="暗角強度 0~1")
    ap.add_argument("--gain", type=float, default=1.0, help="ISO 增益（乘在 code 上，等於類比增益）")
    ap.add_argument("--seed", type=int, default=0)
    ap.add_argument("--preview-max", type=int, default=1200, help="預覽長邊上限（像素，0=原始尺寸）")
    ap.add_argument("--name", default=None, help="輸出檔名前綴")
    ap.add_argument("--out", default="output")
    args = ap.parse_args()

    os.makedirs(args.out, exist_ok=True)
    if args.input:
        img = load_png_linear(args.input, args.input_encode)
    else:
        img = render_preset(args.target, tuple(args.size) if args.size else None)

    if args.size:
        w, h = args.size
        yy = (np.arange(h) * img.shape[0] // h).clip(0, img.shape[0] - 1)
        xx = (np.arange(w) * img.shape[1] // w).clip(0, img.shape[1] - 1)
        img = img[yy][:, xx]

    raw, meta = sensor.simulate_raw(
        img, cfa=args.cfa, wb_gains=tuple(args.wb), exposure=args.exposure,
        bit_depth=args.bits, black_level=args.black, full_well_e=args.full_well,
        read_noise_e=args.read_noise, shot_noise=not args.no_shot_noise,
        vignetting=args.vignette, seed=args.seed)

    if args.gain != 1.0:
        white = meta["white_level"]
        raw = np.clip(np.round(((raw - meta["black_level"]) * args.gain) + meta["black_level"]),
                      0, white).astype(np.uint16)
        meta["analog_gain"] = float(args.gain)

    tag = args.name or (args.target if args.target else os.path.splitext(os.path.basename(args.input))[0])
    base = "%s_bayer%s_%dbits" % (tag, args.cfa, args.bits)
    raw_path = os.path.join(args.out, base + ".raw")
    meta["source"] = args.input or ("gpu:%s" % args.target)
    meta["file"] = os.path.basename(raw_path)
    sensor.save_raw(raw_path, raw, meta)

    # 預覽：去馬賽克 + 還原 WB/曝光 + sRGB 編碼（僅供目視檢查，不是 ISP 成品）
    lin = (raw.astype(np.float32) - meta["black_level"]) / float(meta["white_level"] - meta["black_level"])
    rgb = sensor.demosaic(np.clip(lin, 0, 1), args.cfa)
    wb = np.array(args.wb, dtype=np.float32).reshape(1, 1, 3)
    rgb = np.clip(rgb / np.maximum(wb, 1e-6) / max(args.exposure, 1e-6), 0, 1)

    srgb8 = np.round(linear_to_srgb(rgb) * 255).astype(np.uint8)
    if args.preview_max and max(srgb8.shape[:2]) > args.preview_max:
        from PIL import Image
        h, w = srgb8.shape[:2]
        s = args.preview_max / max(h, w)
        srgb8 = np.asarray(Image.fromarray(srgb8).resize(
            (max(1, int(w * s)), max(1, int(h * s))), Image.LANCZOS))

    prev_path = os.path.join(args.out, base + "_preview.png")
    write_png(prev_path, srgb8, bit_depth=8, compress=3)

    print("CFA=%s  %dx%d  %dbit  黑電平=%d 白電平=%d"
          % (meta["cfa"], meta["width"], meta["height"], meta["bit_depth"],
             meta["black_level"], meta["white_level"]))
    print("已輸出:", raw_path, "(%d bytes)" % os.path.getsize(raw_path))
    print("已輸出:", os.path.splitext(raw_path)[0] + ".json")
    print("已輸出:", prev_path)


if __name__ == "__main__":
    main()
