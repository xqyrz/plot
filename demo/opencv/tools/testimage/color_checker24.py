#!/usr/bin/env python3
"""生成 X-Rite / Calibrite ColorChecker Classic 24 色卡（sRGB 参考值）。

工业视觉里主要用来：白平衡 / 色彩还原 / 相机色彩标定 / ISP CCM 调试。
色块像素值是公认的 sRGB 近似值（D65、gamma2.2），打印后请实测再标定。

用法示例：
  python color_checker24.py                       # 默认 20mm 色块 300dpi
  python color_checker24.py --patch-mm 30 --dpi 600 --labels
  python color_checker24.py --page a4 --dpi 300   # 居中排到 A4 上
"""

import argparse
import os

import numpy as np

import pngio
import seg7

HERE = os.path.dirname(os.path.abspath(__file__))

# 24 色卡：名称 + sRGB
PATCHES = [
    ("dark_skin", 115, 82, 68),
    ("light_skin", 194, 150, 130),
    ("blue_sky", 98, 122, 157),
    ("foliage", 87, 108, 67),
    ("blue_flower", 133, 128, 177),
    ("bluish_green", 103, 189, 170),
    ("orange", 214, 126, 44),
    ("purplish_blue", 80, 91, 166),
    ("moderate_red", 193, 90, 99),
    ("purple", 94, 60, 108),
    ("yellow_green", 157, 188, 64),
    ("orange_yellow", 224, 163, 46),
    ("blue", 56, 61, 150),
    ("green", 70, 148, 73),
    ("red", 175, 54, 60),
    ("yellow", 231, 199, 31),
    ("magenta", 187, 86, 149),
    ("cyan", 8, 133, 161),
    ("white_9.5", 243, 243, 242),
    ("neutral_8", 200, 200, 200),
    ("neutral_6.5", 160, 160, 160),
    ("neutral_5", 122, 122, 121),
    ("neutral_3.5", 85, 85, 85),
    ("black_2", 52, 52, 52),
]

COLS, ROWS = 6, 4


def build(patch_mm=20.0, gap_mm=3.0, margin_mm=10.0, dpi=300,
          labels=False, frame_mm=3.0, border=True):
    """返回 RGB 数组"""
    ps = pngio.mm2px(patch_mm, dpi)
    gp = pngio.mm2px(gap_mm, dpi)
    mg = pngio.mm2px(margin_mm, dpi)

    w = 2 * mg + COLS * ps + (COLS - 1) * gp
    h = 2 * mg + ROWS * ps + (ROWS - 1) * gp
    img = np.full((h, w, 3), 255, dtype=np.uint8)

    for idx, (_, r, g, b) in enumerate(PATCHES):
        cx, cy = idx % COLS, idx // COLS
        x0 = mg + cx * (ps + gp)
        y0 = mg + cy * (ps + gp)
        img[y0:y0 + ps, x0:x0 + ps] = (r, g, b)

        if labels:
            luma = 0.114 * b + 0.587 * g + 0.299 * r
            color = (25, 25, 25) if luma > 128 else (235, 235, 235)
            lh = max(6, ps // 5)
            pad = max(2, lh // 3)
            seg7.draw_digits(img, x0 + pad, y0 + pad, str(idx + 1), lh, color)

    if border and frame_mm > 0:
        fm = max(1, pngio.mm2px(frame_mm, dpi))
        img[:fm, :] = 0
        img[-fm:, :] = 0
        img[:, :fm] = 0
        img[:, -fm:] = 0

    return img


def main():
    ap = argparse.ArgumentParser(description="生成 24 色卡")
    ap.add_argument("-o", "--out", default=os.path.join(HERE, "output", "colorchecker24.png"))
    ap.add_argument("--patch-mm", type=float, default=20.0, help="单色块边长(mm)")
    ap.add_argument("--gap-mm", type=float, default=3.0, help="色块间距(mm)")
    ap.add_argument("--margin-mm", type=float, default=10.0, help="外边距(mm)")
    ap.add_argument("--dpi", type=int, default=300)
    ap.add_argument("--labels", action="store_true", help="在每个色块角上标编号")
    ap.add_argument("--frame-mm", type=float, default=3.0, help="黑色外框宽度(mm)，0=不要")
    ap.add_argument("--page", choices=["none", "a4", "a3", "letter"], default="none")
    args = ap.parse_args()

    img = build(args.patch_mm, args.gap_mm, args.margin_mm, args.dpi,
                args.labels, args.frame_mm, args.frame_mm > 0)
    if args.page != "none":
        img = pngio.center_on_page(img, args.page, args.dpi)

    pngio.ensure_dir(args.out)
    pngio.write_png(args.out, img, dpi=args.dpi)
    print("wrote %s  (%dx%d, %.1fx%.1fmm)"
          % (args.out, img.shape[1], img.shape[0],
             img.shape[1] / args.dpi * 25.4, img.shape[0] / args.dpi * 25.4))


if __name__ == "__main__":
    main()
