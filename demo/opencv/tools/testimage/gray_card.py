#!/usr/bin/env python3
"""生成灰阶测试卡：分阶灰块 + 连续灰阶楔（灰度响应 / gamma / 曝光 / 噪声评估用）。

--gamma 2.2 时，各级灰度按感知均匀分布（和柯达 Q-13/Q-14、X-Rite 灰阶卡接近）；
--gamma 1.0 时就是严格的等间隔 0~255（做线性度、位深评估更合适）。

用法示例：
  python gray_card.py                          # 21 阶 + 连续楔
  python gray_card.py --steps 11 --gamma 1 --wedge none
  python gray_card.py --size-mm 120 --dpi 600
"""

import argparse
import os

import numpy as np

import pngio
import seg7

HERE = os.path.dirname(os.path.abspath(__file__))


def build(steps=21, gamma=2.2, step_mm=15.0, gap_mm=0.0, dpi=300,
          wedge="bottom", wedge_mm=12.0, margin_mm=8.0, labels=True):
    """返回灰度图"""
    sp = pngio.mm2px(step_mm, dpi)
    gp = pngio.mm2px(gap_mm, dpi)
    mg = pngio.mm2px(margin_mm, dpi)
    wp = pngio.mm2px(wedge_mm, dpi)

    w = 2 * mg + steps * sp + (steps - 1) * gp
    extra = (mg + wp + (mg // 2)) if wedge == "bottom" else 0
    h = 2 * mg + sp + extra
    img = np.full((h, w), 255, dtype=np.uint8)

    for i in range(steps):
        t = i / (steps - 1)
        v = int(round(255 * (t ** gamma)))
        x0 = mg + i * (sp + gp)
        y0 = mg
        img[y0:y0 + sp, x0:x0 + sp] = v

        if labels:
            # 灰度值写在灰块下沿，浅底用深字、深底用浅字
            lh = max(6, sp // 5)
            color = 20 if v > 128 else 235
            tw = seg7.text_width(str(v), lh)
            seg7.draw_digits(img, x0 + max(0, (sp - tw) // 2),
                             y0 + sp - lh - max(2, lh // 2), str(v), lh, color)

    if wedge == "bottom":
        y0 = mg + sp + (mg // 2)
        ramp = np.arange(w - 2 * mg, dtype=np.float32)
        ramp = ramp / max(1, ramp.size - 1)
        row = np.round(255 * ramp).astype(np.uint8)
        img[y0:y0 + wp, mg:w - mg] = row[None, :]

    return img


def main():
    ap = argparse.ArgumentParser(description="生成灰阶测试卡")
    ap.add_argument("-o", "--out", default=os.path.join(HERE, "output", "gray_card_21.png"))
    ap.add_argument("--steps", type=int, default=21, help="灰阶级数")
    ap.add_argument("--gamma", type=float, default=2.2, help="灰阶分布 gamma，1.0=等间隔")
    ap.add_argument("--step-mm", type=float, default=15.0, help="单级宽度(mm)")
    ap.add_argument("--gap-mm", type=float, default=0.0, help="灰块间距(mm)")
    ap.add_argument("--wedge-mm", type=float, default=12.0, help="连续楔高度(mm)")
    ap.add_argument("--wedge", choices=["bottom", "none"], default="bottom")
    ap.add_argument("--margin-mm", type=float, default=8.0)
    ap.add_argument("--dpi", type=int, default=300)
    ap.add_argument("--no-labels", action="store_true")
    ap.add_argument("--page", choices=["none", "a4", "a3", "letter"], default="none")
    args = ap.parse_args()

    img = build(args.steps, args.gamma, args.step_mm, args.gap_mm, args.dpi,
                args.wedge, args.wedge_mm, args.margin_mm, not args.no_labels)
    if args.page != "none":
        img = pngio.center_on_page(img, args.page, args.dpi)

    pngio.ensure_dir(args.out)
    pngio.write_png(args.out, img, dpi=args.dpi)
    print("wrote %s  (%dx%d)"
          % (args.out, img.shape[1], img.shape[0]))


if __name__ == "__main__":
    main()
