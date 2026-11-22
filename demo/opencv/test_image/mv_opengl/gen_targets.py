# -*- coding: utf-8 -*-
"""生成其他常用機器視覺標靶（OpenGL 離屏渲染）。

可用 target：
    circle_grid   非對稱圓點陣列（OpenCV CALIB_CB_ASYMMETRIC_GRID）
    siemens       西門子星（對焦 / 極限解析度）
    gray_wedge    階梯灰卡（動態範圍、Gamma、SNR）
    slanted_edge  斜邊靶（ISO12233 MTF / SFR）
    zone_plate    區域板（解析度極限、摩爾紋、去馬賽克）
    flat          平場（暗角、白平衡、壞點）
    dots          隨機點陣（幾何畸變、特徵點密度）

範例
----
    python gen_targets.py --target circle_grid --cols 11 --rows 8
    python gen_targets.py --target siemens --size 2000 --spokes 72
    python gen_targets.py --target all
"""
import argparse
import os

import mvgl.targets as T


def build(name, a):
    if name == "circle_grid":
        return T.circle_grid(cols=a.cols, rows=a.rows, spacing=a.spacing,
                             ssaa=a.ssaa), "circle_grid_%dx%d_s%d.png" % (a.cols, a.rows, a.spacing)
    if name == "siemens":
        return T.siemens_star(size=a.size, spokes=a.spokes, ssaa=a.ssaa), "siemens_star_%d_s%d.png" % (a.size, a.spokes)
    if name == "gray_wedge":
        img, meta = T.gray_wedge(steps=a.steps, patch_w=a.patch_px, height=a.height,
                                 srgb_steps=not a.linear_steps, vertical=a.vertical, ssaa=a.ssaa)
        return (img, meta), "gray_wedge_%d_steps%s.png" % (a.steps, "_v" if a.vertical else "")
    if name == "slanted_edge":
        return T.slanted_edge(size=a.size, angle=a.angle, ssaa=a.ssaa), "slanted_edge_%d_%.1fdeg.png" % (a.size, a.angle)
    if name == "zone_plate":
        return T.zone_plate(size=a.size, k=a.k, ssaa=max(2, a.ssaa - 1)), "zone_plate_%d.png" % a.size
    if name == "flat":
        return T.flat_field(size=(a.width, a.height), ssaa=2), "flat_field_%dx%d.png" % (a.width, a.height)
    if name == "dots":
        return T.random_dots(size=(a.width, a.height), seed=a.seed, ssaa=2), "random_dots_%dx%d_s%d.png" % (a.width, a.height, a.seed)
    raise SystemExit("未知 target: %s" % name)


def main():
    ap = argparse.ArgumentParser(description="其他機器視覺標靶生成器（OpenGL）")
    ap.add_argument("--target", default="circle_grid",
                    choices=["circle_grid", "siemens", "gray_wedge", "slanted_edge",
                             "zone_plate", "flat", "dots", "all"])
    ap.add_argument("--cols", type=int, default=11)
    ap.add_argument("--rows", type=int, default=8)
    ap.add_argument("--spacing", type=int, default=64, help="圓點間距（像素）")
    ap.add_argument("--size", type=int, default=1600)
    ap.add_argument("--spokes", type=int, default=72)
    ap.add_argument("--steps", type=int, default=21)
    ap.add_argument("--patch-px", type=int, default=120)
    ap.add_argument("--height", type=int, default=400)
    ap.add_argument("--width", type=int, default=1920)
    ap.add_argument("--angle", type=float, default=5.0)
    ap.add_argument("--k", type=float, default=120.0)
    ap.add_argument("--seed", type=int, default=7)
    ap.add_argument("--vertical", action="store_true")
    ap.add_argument("--linear-steps", action="store_true", help="灰階級值以線性光定義（預設為 sRGB 編碼值）")
    ap.add_argument("--ssaa", type=int, default=4)
    ap.add_argument("--bits", type=int, default=8, choices=[8, 16])
    ap.add_argument("--out", default="output")
    args = ap.parse_args()

    os.makedirs(args.out, exist_ok=True)
    names = ["circle_grid", "siemens", "gray_wedge", "slanted_edge", "zone_plate", "flat", "dots"] \
        if args.target == "all" else [args.target]

    for n in names:
        (img, meta), fname = build(n, args)
        path = os.path.join(args.out, fname)
        T.save(img, path, bit_depth=args.bits, encode="srgb", dpi=300)
        T.save_meta(path, meta)
        print("%-13s -> %s  (%dx%d)" % (n, path, meta["size"][0], meta["size"][1]))


if __name__ == "__main__":
    main()
