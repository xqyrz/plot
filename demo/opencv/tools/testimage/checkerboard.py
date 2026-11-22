#!/usr/bin/env python3
"""生成棋盘格标定板（OpenCV findChessboardCorners / findCirclesGrid 常用）。

--cols/--rows 指的是**内角点个数**（OpenCV 的 pattern_size），
实际黑白方块数是 (cols+1) x (rows+1)，这点和标定代码里的参数直接对应。

用法示例：
  python checkerboard.py                                   # 9x6 内角点, 20mm 方块
  python checkerboard.py --cols 11 --rows 8 --square-mm 15 --dpi 600
  python checkerboard.py --page a4 --dpi 300               # 打印到 A4
  python checkerboard.py --invert                          # 黑底白格（背光/投影用）
"""

import argparse
import os

import numpy as np

import pngio

HERE = os.path.dirname(os.path.abspath(__file__))


def build(cols=9, rows=6, square_mm=20.0, dpi=300, margin_mm=10.0,
          invert=False, border_mm=0.0, origin_black=True):
    """cols/rows = 内角点数，返回灰度图"""
    sq = pngio.mm2px(square_mm, dpi)
    mg = pngio.mm2px(margin_mm, dpi)
    bm = pngio.mm2px(border_mm, dpi) if border_mm > 0 else 0

    nx, ny = cols + 1, rows + 1          # 方块个数
    w = 2 * mg + nx * sq + 2 * bm
    h = 2 * mg + ny * sq + 2 * bm

    dark, light = (0, 255) if not invert else (255, 0)
    bg = 255 if not invert else 0
    img = np.full((h, w), bg, dtype=np.uint8)

    for j in range(ny):
        for i in range(nx):
            is_black = ((i + j) % 2 == 0) == origin_black
            v = dark if is_black else light
            x0 = mg + bm + i * sq
            y0 = mg + bm + j * sq
            img[y0:y0 + sq, x0:x0 + sq] = v

    # 外面一圈实心边框：给找角点当边界参考，也方便判断是否裁切
    if bm:
        img[:bm, :] = dark
        img[-bm:, :] = dark
        img[:, :bm] = dark
        img[:, -bm:] = dark

    return img


def main():
    ap = argparse.ArgumentParser(description="生成棋盘格标定板")
    ap.add_argument("-o", "--out", default=os.path.join(HERE, "output", "checkerboard_9x6.png"))
    ap.add_argument("--cols", type=int, default=9, help="内角点列数")
    ap.add_argument("--rows", type=int, default=6, help="内角点行数")
    ap.add_argument("--square-mm", type=float, default=20.0, help="单格边长(mm)")
    ap.add_argument("--dpi", type=int, default=300)
    ap.add_argument("--margin-mm", type=float, default=10.0, help="白边(mm)")
    ap.add_argument("--border-mm", type=float, default=0.0, help="四周黑框宽度(mm)")
    ap.add_argument("--invert", action="store_true", help="黑底白格")
    ap.add_argument("--origin-white", action="store_true", help="左上第一格为白色")
    ap.add_argument("--page", choices=["none", "a4", "a3", "letter"], default="none")
    args = ap.parse_args()

    img = build(args.cols, args.rows, args.square_mm, args.dpi, args.margin_mm,
                args.invert, args.border_mm, origin_black=not args.origin_white)
    if args.page != "none":
        img = pngio.center_on_page(img, args.page, args.dpi)

    pngio.ensure_dir(args.out)
    pngio.write_png(args.out, img, dpi=args.dpi)
    print("wrote %s  (%dx%d, %.1fx%.1fmm, 内角点 %dx%d)"
          % (args.out, img.shape[1], img.shape[0],
             img.shape[1] / args.dpi * 25.4, img.shape[0] / args.dpi * 25.4,
             args.cols, args.rows))


if __name__ == "__main__":
    main()
