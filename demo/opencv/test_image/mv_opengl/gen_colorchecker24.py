# -*- coding: utf-8 -*-
"""生成 24 色卡（X-Rite ColorChecker Classic 佈局）——OpenGL 離屏渲染。

範例
----
    python gen_colorchecker24.py                      # 預設 1280x1920, 8bit sRGB + 16bit 線性
    python gen_colorchecker24.py --patch-px 480 --labels
    python gen_colorchecker24.py --ssaa 8 --bits 16
"""
import argparse
import os

import numpy as np

import mvgl.targets as T
from mvgl.color import COLORCHECKER_24, linear_to_srgb


def add_labels(img_linear, patch_px, path):
    """用 PIL 在色塊角落標編號（GLSL 畫字很麻煩，這裡走 2D 疊加）。"""
    try:
        from PIL import Image, ImageDraw, ImageFont
    except ImportError:
        print("[warn] 未安裝 pillow，跳過 --labels")
        return None

    arr = np.round(np.clip(linear_to_srgb(img_linear), 0, 1) * 255).astype(np.uint8)
    im = Image.fromarray(arr).convert("RGB")
    draw = ImageDraw.Draw(im)
    size = max(12, int(patch_px * 0.09))
    try:
        font = ImageFont.load_default(size=size)
    except TypeError:
        font = ImageFont.load_default()

    h, w = arr.shape[:2]
    px = w // 4
    for i in range(24):
        r, c = divmod(i, 4)
        x = c * px + int(px * 0.06)
        y = r * px + int(px * 0.06)
        # 依色塊亮度選黑/白字，保證可讀
        lum = float(np.mean(arr[r * px + px // 2, c * px + px // 2]))
        txt = str(i + 1)
        draw.text((x + 2, y + 2), txt, fill=(0, 0, 0) if lum > 110 else (255, 255, 255), font=font)
        draw.text((x, y), txt, fill=(255, 255, 255) if lum > 110 else (0, 0, 0), font=font)
    im.save(path)
    return path


def main():
    ap = argparse.ArgumentParser(description="24 色卡生成器（OpenGL）")
    ap.add_argument("--patch-px", type=int, default=320, help="單個色塊邊長（像素），整卡 = 4×6 個")
    ap.add_argument("--pad", type=float, default=0.045, help="色塊之間留白比例")
    ap.add_argument("--ssaa", type=int, default=4, help="超取樣倍數（抗鋸齒/亞像素邊緣）")
    ap.add_argument("--bits", type=int, default=8, choices=[8, 16])
    ap.add_argument("--labels", action="store_true", help="額外輸出一張帶編號的預覽")
    ap.add_argument("--out", default="output")
    args = ap.parse_args()

    os.makedirs(args.out, exist_ok=True)
    img, meta = T.colorchecker(patch_px=args.patch_px, pad=args.pad, ssaa=args.ssaa)

    srgb8 = os.path.join(args.out, "colorchecker24_srgb8.png")
    lin16 = os.path.join(args.out, "colorchecker24_linear16.png")
    T.save(img, srgb8, bit_depth=8, encode="srgb", dpi=300)
    T.save(img, lin16, bit_depth=16, encode="linear", dpi=300)
    T.save_meta(srgb8, meta)

    print("GPU: %s" % T.renderer().renderer_name)
    print("尺寸: %dx%d  (單塊 %d px)" % (meta["size"][0], meta["size"][1], args.patch_px))
    print("已輸出:", srgb8)
    print("已輸出:", lin16, "(16bit 線性，供量測/RAW 模擬)")
    if args.labels:
        print("已輸出:", add_labels(img, args.patch_px, os.path.join(args.out, "colorchecker24_labeled.png")))

    # 自我檢查：色塊中心應還原標稱 sRGB 值
    px = args.patch_px
    vals = []
    for i in range(24):
        r, c = divmod(i, 4)
        v = np.round(np.clip(linear_to_srgb(img[r * px + px // 2, c * px + px // 2]), 0, 1) * 255)
        vals.append(tuple(int(x) for x in v))
    ok = all(max(abs(a - b) for a, b in zip(vals[i], COLORCHECKER_24[i][1])) <= 1 for i in range(24))
    print("色彩自檢:", "通過（與標稱值差 ≤1 LSB）" if ok else "偏差過大")


if __name__ == "__main__":
    main()
