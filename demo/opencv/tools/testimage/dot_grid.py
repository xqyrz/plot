#!/usr/bin/env python3
"""生成圆点标定板（OpenCV findCirclesGrid，对称/非对称网格都可）。

相比棋盘格：圆心提取对镜头畸变、离焦更稳，工业上很常用。

用法示例：
  python dot_grid.py                                  # 7x7 对称网格
  python dot_grid.py --cols 11 --rows 8 --spacing-mm 10 --dot-mm 4
  python dot_grid.py --asymmetric --page a4 --dpi 300
"""

import argparse
import os

import numpy as np

import pngio

HERE = os.path.dirname(os.path.abspath(__file__))


def build(cols=7, rows=7, spacing_mm=15.0, dot_mm=6.0, dpi=300,
          margin_mm=10.0, invert=False, asymmetric=False, ss=4):
    """返回灰度图。ss = 超采样倍数，用来把圆边缘做平滑"""
    sp = pngio.mm2px(spacing_mm, dpi)
    dm = pngio.mm2px(dot_mm, dpi)
    mg = pngio.mm2px(margin_mm, dpi)

    # 非对称网格（findCirclesGrid ASYMMETRIC_GRID）是交错排列
    if asymmetric:
        eff_cols = 2 * cols - 1
    else:
        eff_cols = cols
    eff_rows = rows

    w = 2 * mg + (eff_cols - 1) * sp + dm
    h = 2 * mg + (eff_rows - 1) * sp + dm

    bg = 255 if not invert else 0
    fg = 0 if not invert else 255

    # 超采样画圆：先放大 ss 倍算距离场，再降采样
    hb, wb = h * ss, w * ss
    acc = np.zeros((hb, wb), dtype=np.float32)
    r = dm * ss / 2.0

    for j in range(eff_rows):
        yc = (mg + j * sp + dm / 2.0) * ss
        for i in range(eff_cols):
            # 交错网格：偶数行放偶数位置，奇数行放奇数位置（每行仍是 cols 个点）
            if asymmetric and (i + j) % 2 == 1:
                continue
            xc = (mg + i * sp + dm / 2.0) * ss
            if xc + r > wb:
                continue

            x0 = max(0, int(xc - r) - 1)
            x1 = min(wb, int(xc + r) + 2)
            y0 = max(0, int(yc - r) - 1)
            y1 = min(hb, int(yc + r) + 2)
            yy, xx = np.ogrid[y0:y1, x0:x1]
            # 距离<r 置 1；边界 1px 内做软过渡（抗锯齿）
            d = np.sqrt((xx - xc) ** 2 + (yy - yc) ** 2)
            cov = np.clip(r + 0.5 - d, 0.0, 1.0)
            acc[y0:y1, x0:x1] = np.maximum(acc[y0:y1, x0:x1], cov)

    # 降采样回原尺寸
    cov = acc.reshape(h, ss, w, ss).mean(axis=(1, 3))
    img = (bg + (fg - bg) * cov).astype(np.uint8)
    return img


def main():
    ap = argparse.ArgumentParser(description="生成圆点标定板")
    ap.add_argument("-o", "--out", default=os.path.join(HERE, "output", "dotgrid_7x7.png"))
    ap.add_argument("--cols", type=int, default=7, help="列数（非对称时为左半列数）")
    ap.add_argument("--rows", type=int, default=7, help="行数")
    ap.add_argument("--spacing-mm", type=float, default=15.0)
    ap.add_argument("--dot-mm", type=float, default=6.0, help="圆点直径(mm)")
    ap.add_argument("--dpi", type=int, default=300)
    ap.add_argument("--margin-mm", type=float, default=10.0)
    ap.add_argument("--invert", action="store_true", help="黑底白点")
    ap.add_argument("--asymmetric", action="store_true", help="交错（非对称）网格")
    ap.add_argument("--page", choices=["none", "a4", "a3", "letter"], default="none")
    args = ap.parse_args()

    img = build(args.cols, args.rows, args.spacing_mm, args.dot_mm, args.dpi,
                args.margin_mm, args.invert, args.asymmetric)
    if args.page != "none":
        img = pngio.center_on_page(img, args.page, args.dpi)

    pngio.ensure_dir(args.out)
    pngio.write_png(args.out, img, dpi=args.dpi)
    print("wrote %s  (%dx%d)"
          % (args.out, img.shape[1], img.shape[0]))


if __name__ == "__main__":
    main()
