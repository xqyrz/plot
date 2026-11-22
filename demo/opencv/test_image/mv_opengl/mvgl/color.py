# -*- coding: utf-8 -*-
"""色彩空間與色卡資料。"""
import numpy as np

# ── 24 色卡（X-Rite ColorChecker Classic）標準 sRGB 8bit 標稱值 ──
# 順序：由上到下、由左到右，4 欄 × 6 列
COLORCHECKER_24 = [
    ("dark skin",      (115,  82,  68)),
    ("light skin",     (194, 150, 130)),
    ("blue sky",       ( 98, 122, 157)),
    ("foliage",        ( 87, 108,  67)),
    ("blue flower",    (133, 128, 177)),
    ("bluish green",   (103, 189, 170)),

    ("orange",         (214, 126,  44)),
    ("purplish blue",  ( 80,  91, 166)),
    ("moderate red",   (193,  90,  99)),
    ("purple",         ( 94,  60, 108)),
    ("yellow green",   (157, 188,  64)),
    ("orange yellow",  (224, 163,  46)),

    ("blue",           ( 56,  61, 150)),
    ("green",          ( 70, 148,  73)),
    ("red",            (175,  54,  60)),
    ("yellow",         (231, 199,  31)),
    ("magenta",        (187,  86, 149)),
    ("cyan",           (  8, 133, 161)),

    ("white",          (243, 243, 242)),
    ("neutral 8",      (200, 200, 200)),
    ("neutral 6.5",    (160, 160, 160)),
    ("neutral 5",      (122, 122, 121)),
    ("neutral 3.5",    ( 85,  85,  85)),
    ("black",          ( 52,  52,  52)),
]


def srgb_to_linear(c):
    """sRGB (0..1) -> 線性光 (0..1)。"""
    c = np.asarray(c, dtype=np.float64)
    return np.where(c <= 0.04045, c / 12.92, ((c + 0.055) / 1.055) ** 2.4)


def linear_to_srgb(c):
    """線性光 (0..1) -> sRGB (0..1)。"""
    c = np.asarray(c, dtype=np.float64)
    c = np.clip(c, 0.0, 1.0)
    return np.where(c <= 0.0031308, c * 12.92, 1.055 * c ** (1.0 / 2.4) - 0.055)


def colorchecker_linear():
    """回傳 (names, linear RGB float32 (24,3))。"""
    names = [n for n, _ in COLORCHECKER_24]
    rgb8 = np.array([v for _, v in COLORCHECKER_24], dtype=np.float64) / 255.0
    return names, srgb_to_linear(rgb8).astype(np.float32)
