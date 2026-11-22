# -*- coding: utf-8 -*-
"""各種標靶的高階生成介面：算好參數 -> 丟給 GPU -> 輸出線性影像。"""
import json
import os

import numpy as np

from . import shaders
from .color import COLORCHECKER_24, colorchecker_linear
from .context import GLRenderer
from .pngio import write_png

_RENDERER = None


def renderer():
    global _RENDERER
    if _RENDERER is None:
        _RENDERER = GLRenderer(require=330)
    return _RENDERER


def finish(img_linear, bit_depth=8, encode="srgb", dither=True, seed=0):
    """線性影像 -> 可存檔陣列。encode: 'srgb'（顯示/列印）或 'linear'（量測用）。"""
    from .color import linear_to_srgb
    img = np.clip(img_linear, 0.0, 1.0)
    if encode == "srgb":
        img = linear_to_srgb(img)
    levels = 255.0 if bit_depth == 8 else 65535.0
    if dither:
        rng = np.random.default_rng(seed)
        img = np.clip(img + (rng.random(img.shape) - 0.5) / levels * 1.5, 0.0, 1.0)
    arr = np.round(img * levels)
    return arr.astype(np.uint8 if bit_depth == 8 else np.uint16)


def save(img_linear, path, bit_depth=8, encode="srgb", dpi=None, compress=9):
    arr = finish(img_linear, bit_depth, encode)
    write_png(path, arr, bit_depth=bit_depth, dpi=dpi, compress=compress)
    return path


def save_meta(path, meta):
    with open(os.path.splitext(path)[0] + ".json", "w", encoding="utf-8") as f:
        json.dump(meta, f, indent=2, ensure_ascii=False)


# ───────────────────────── 24 色卡 ─────────────────────────
def colorchecker(patch_px=320, pad=0.045, ssaa=4, grid=(4, 6)):
    names, lin = colorchecker_linear()
    w = grid[0] * patch_px
    h = grid[1] * patch_px
    # 卡紙（深灰）與色塊間的分隔線
    uniforms = {
        "u_res": (float(w), float(h)),
        "u_patches": lin.reshape(-1),          # vec3[24] 攤平
        "u_grid": (float(grid[0]), float(grid[1])),
        "u_pad": float(pad),
        "u_card": (0.045, 0.045, 0.048),
        "u_frame": (0.02, 0.02, 0.021),
    }
    img = renderer().render(shaders.COLORCHECKER, uniforms, size=(w, h), ssaa=ssaa)
    meta = {
        "target": "colorchecker24",
        "size": [w, h],
        "grid": list(grid),
        "patch_px": patch_px,
        "pad_ratio": pad,
        "patch_order": names,
        "srgb8_values": [list(map(int, v)) for _, v in COLORCHECKER_24],
        "note": "色塊以標準 sRGB 標稱值轉線性後渲染；輸出 PNG 再經 sRGB 編碼，故 8bit 值≈標稱值。",
    }
    return img, meta


# ───────────────────────── 棋盤格 ─────────────────────────
def chessboard(cols=10, rows=7, square_px=120, margin_squares=1, ssaa=4, invert=False):
    sq = int(square_px)
    m = int(margin_squares) * sq
    w = cols * sq + 2 * m
    h = rows * sq + 2 * m
    uniforms = {
        "u_res": (float(w), float(h)),
        "u_cells": (float(cols), float(rows)),
        "u_margin": (m / w, m / h),
        "u_invert": 1.0 if invert else 0.0,
        "u_bg": 1.0,
    }
    img = renderer().render(shaders.CHESSBOARD, uniforms, size=(w, h), ssaa=ssaa)
    meta = {
        "target": "chessboard",
        "size": [w, h],
        "squares": [cols, rows],
        "square_px": sq,
        "margin_px": m,
        "inner_corners": [cols - 1, rows - 1],
        "note": "內角點 = (方格數-1)；列印時整板物理尺寸 = 邊長 × 方格數。",
    }
    return img, meta


# ───────────────────── 非對稱圓點陣列 ─────────────────────
def circle_grid(cols=11, rows=8, spacing=64, radius_ratio=0.42, margin_cells=1.0, ssaa=4):
    sp = float(spacing)
    rad = sp * radius_ratio
    m = sp * margin_cells
    w = int(round((cols - 1) * sp + 0.5 * sp + 2 * m))
    h = int(round((rows - 1) * sp + 2 * m))
    origin = (m, m)
    uniforms = {
        "u_res": (float(w), float(h)),
        "u_count": (float(cols), float(rows)),
        "u_spacing": sp,
        "u_radius": rad,
        "u_origin": origin,
        "u_stagger": 0.5,
        "u_bg": 1.0,
    }
    img = renderer().render(shaders.CIRCLE_GRID, uniforms, size=(w, h), ssaa=ssaa)
    meta = {
        "target": "asymmetric_circle_grid",
        "size": [w, h],
        "points": [cols, rows],
        "spacing_px": sp,
        "radius_px": rad,
        "opencv_flag": "CALIB_CB_ASYMMETRIC_GRID",
    }
    return img, meta


# ───────────────────── 西門子星 / 灰階 / 斜邊 ─────────────────────
def siemens_star(size=1600, spokes=72, radius_ratio=0.46, ssaa=4):
    s = int(size)
    uniforms = {
        "u_res": (float(s), float(s)),
        "u_spokes": float(spokes),
        "u_center": (s / 2.0, s / 2.0),
        "u_radius": s * radius_ratio,
        "u_bg": 1.0,
    }
    img = renderer().render(shaders.SIEMENS_STAR, uniforms, size=(s, s), ssaa=ssaa)
    return img, {"target": "siemens_star", "size": [s, s], "spokes": spokes}


def gray_wedge(steps=21, patch_w=160, height=400, srgb_steps=True, vertical=False, ssaa=4):
    if vertical:
        w, h = int(patch_w), int(patch_w) * steps
    else:
        w, h = int(patch_w) * steps, int(height)
    uniforms = {
        "u_res": (float(w), float(h)),
        "u_steps": float(steps),
        "u_srgb": 1.0 if srgb_steps else 0.0,
        "u_vertical": 1.0 if vertical else 0.0,
    }
    img = renderer().render(shaders.GRAY_WEDGE, uniforms, size=(w, h), ssaa=ssaa)
    return img, {"target": "gray_wedge", "size": [w, h], "steps": steps, "srgb_defined": srgb_steps}


def slanted_edge(size=1024, angle=5.0, half=0.33, ssaa=4):
    s = int(size)
    uniforms = {
        "u_res": (float(s), float(s)),
        "u_angle": float(angle),
        "u_half": float(half),
    }
    img = renderer().render(shaders.SLANTED_EDGE, uniforms, size=(s, s), ssaa=ssaa)
    return img, {"target": "slanted_edge", "size": [s, s], "angle_deg": angle,
                 "box_half_ratio": half, "standard": "ISO 12233 / MTF SFR"}


def zone_plate(size=1400, k=120.0, ssaa=3):
    s = int(size)
    uniforms = {
        "u_res": (float(s), float(s)),
        "u_k": float(k),
        "u_center": (s / 2.0, s / 2.0),
        "u_bg": 0.0,
    }
    img = renderer().render(shaders.ZONE_PLATE, uniforms, size=(s, s), ssaa=ssaa)
    return img, {"target": "zone_plate", "size": [s, s], "k": k}


def flat_field(size=(1920, 1080), rgb=(1.0, 1.0, 1.0), ssaa=2):
    w, h = size
    uniforms = {"u_res": (float(w), float(h)), "u_color": tuple(float(c) for c in rgb)}
    img = renderer().render(shaders.FLAT_FIELD, uniforms, size=(w, h), ssaa=ssaa)
    return img, {"target": "flat_field", "size": [w, h], "linear_rgb": list(rgb)}


def random_dots(size=(1920, 1080), density=0.6, radius=3.0, seed=7, ssaa=2):
    w, h = size
    uniforms = {
        "u_res": (float(w), float(h)),
        "u_density": float(density),
        "u_radius": float(radius),
        "u_seed": float(seed),
        "u_bg": 1.0,
    }
    img = renderer().render(shaders.RANDOM_DOTS, uniforms, size=(w, h), ssaa=ssaa)
    return img, {"target": "random_dots", "size": [w, h], "seed": seed}
