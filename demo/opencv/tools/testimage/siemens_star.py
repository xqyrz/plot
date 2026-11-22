#!/usr/bin/env python3
"""生成西门子星（Siemens star）分辨率测试卡。

用途：量中心/边缘的极限分辨率、看镜头调制传递特性（MTF 走刀口法也可以用它近似看）、
      以及检查是否存在方向性模糊（各方向扇形对比）。

用法示例：
  python siemens_star.py                                  # 36 扇区, 100mm
  python siemens_star.py --spokes 72 --diameter-mm 80 --dpi 600
"""

import argparse
import os

import numpy as np

import pngio

HERE = os.path.dirname(os.path.abspath(__file__))


def build(spokes=36, diameter_mm=100.0, dpi=300, margin_mm=8.0,
          ss=4, invert=False, center_dot_mm=2.0, ring=True):
    """返回灰度图。spokes = 扇区总数（偶数）"""
    d = pngio.mm2px(diameter_mm, dpi)
    mg = pngio.mm2px(margin_mm, dpi)
    w = h = d + 2 * mg

    # 超采样算角度，再平均，得到平滑的扇区边界
    hb, wb = h * ss, w * ss
    y, x = np.mgrid[0:hb, 0:wb].astype(np.float32)
    cx, cy = wb / 2.0, hb / 2.0
    dx, dy = x - cx, y - cy
    r = np.sqrt(dx * dx + dy * dy)
    theta = np.arctan2(dy, dx) + np.pi
    sector = np.floor(theta / (2 * np.pi) * 2 * spokes).astype(np.int32)

    dark, light = (0, 255) if not invert else (255, 0)
    bg = 255 if not invert else 0
    mask = r <= d * ss / 2.0
    cov = (sector % 2).astype(np.float32)

    if ring:
        # 外圈细黑边，便于对焦和判断视场覆盖
        rr = 4 * ss
        band = (r > (d * ss / 2.0 - rr)) & (r <= d * ss / 2.0)
        cov[band] = 0.0 if not invert else 1.0

    if center_dot_mm > 0:
        cd = pngio.mm2px(center_dot_mm, dpi) * ss / 2.0
        cov[r <= cd] = 0.0 if not invert else 1.0

    outside = bg / 255.0
    cov = np.where(mask | (ring & mask), cov, outside)

    img = cov.reshape(h, ss, w, ss).mean(axis=(1, 3))
    img = np.round(img * 255).astype(np.uint8)
    return img


def main():
    ap = argparse.ArgumentParser(description="生成西门子星分辨率卡")
    ap.add_argument("-o", "--out", default=os.path.join(HERE, "output", "siemens_star_36.png"))
    ap.add_argument("--spokes", type=int, default=36, help="扇区总数")
    ap.add_argument("--diameter-mm", type=float, default=100.0)
    ap.add_argument("--dpi", type=int, default=300)
    ap.add_argument("--margin-mm", type=float, default=8.0)
    ap.add_argument("--center-dot-mm", type=float, default=2.0, help="中心圆点直径，0=不要")
    ap.add_argument("--no-ring", action="store_true", help="不要外圈细边")
    ap.add_argument("--invert", action="store_true", help="黑底白扇区")
    ap.add_argument("--page", choices=["none", "a4", "a3", "letter"], default="none")
    args = ap.parse_args()

    img = build(args.spokes, args.diameter_mm, args.dpi, args.margin_mm,
                invert=args.invert, center_dot_mm=args.center_dot_mm,
                ring=not args.no_ring)
    if args.page != "none":
        img = pngio.center_on_page(img, args.page, args.dpi)

    pngio.ensure_dir(args.out)
    pngio.write_png(args.out, img, dpi=args.dpi)
    print("wrote %s  (%dx%d)" % (args.out, img.shape[1], img.shape[0]))


if __name__ == "__main__":
    main()
