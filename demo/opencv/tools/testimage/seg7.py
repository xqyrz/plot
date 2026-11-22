#!/usr/bin/env python3
"""用 7 段数码管风格在图像上画数字，给测试图加编号，不依赖字体库。

段编号：
      a
   f     b
      g
   e     c
      d
"""

import numpy as np

# a, b, c, d, e, f, g
_SEG = {
    "0": (1, 1, 1, 1, 1, 1, 0),
    "1": (0, 1, 1, 0, 0, 0, 0),
    "2": (1, 1, 0, 1, 1, 0, 1),
    "3": (1, 1, 1, 1, 0, 0, 1),
    "4": (0, 1, 1, 0, 0, 1, 1),
    "5": (1, 0, 1, 1, 0, 1, 1),
    "6": (1, 0, 1, 1, 1, 1, 1),
    "7": (1, 1, 1, 0, 0, 0, 0),
    "8": (1, 1, 1, 1, 1, 1, 1),
    "9": (1, 1, 1, 1, 0, 1, 1),
    "-": (0, 0, 0, 0, 0, 0, 1),
}


def _fill(img, x0, y0, x1, y1, color):
    h, w = img.shape[:2]
    x0, x1 = max(0, x0), min(w, x1)
    y0, y1 = max(0, y0), min(h, y1)
    if x1 <= x0 or y1 <= y0:
        return
    img[y0:y1, x0:x1] = color


def _digit(img, x, y, ch, height, color):
    """在 (x, y) 左上角画一个字符，返回字符宽度"""
    if ch not in _SEG:
        return int(round(height * 0.45))

    t = max(2, int(round(height * 0.11)))
    w = int(round(height * 0.55))
    segs = _SEG[ch]

    mid = y + height // 2
    xl, xr = x, x + w - t
    # a 上横
    if segs[0]:
        _fill(img, x + t, y, x + w - t, y + t, color)
    # b 右上竖
    if segs[1]:
        _fill(img, xr, y + t, x + w, mid, color)
    # c 右下竖
    if segs[2]:
        _fill(img, xr, mid, x + w, y + height - t, color)
    # d 下横
    if segs[3]:
        _fill(img, x + t, y + height - t, x + w - t, y + height, color)
    # e 左下竖
    if segs[4]:
        _fill(img, xl, mid, x + t, y + height - t, color)
    # f 左上竖
    if segs[5]:
        _fill(img, xl, y + t, x + t, mid, color)
    # g 中横
    if segs[6]:
        _fill(img, x + t, mid - t // 2, x + w - t, mid - t // 2 + t, color)

    return w


def draw_digits(img, x, y, text, height, color, gap=None):
    """在 img 上画一串数字，返回总宽度。

    参数：
      height  数字高度（像素），决定整体大小
      color   灰度值或 (r,g,b)
      gap     字符间距，默认 height*0.18
    """
    if gap is None:
        gap = max(2, int(round(height * 0.18)))
    start_x = x
    for ch in str(text):
        if ch == " ":
            x += int(round(height * 0.35))
            continue
        w = _digit(img, x, y, ch, height, color)
        x += w + gap
    return x - gap - start_x


def text_width(text, height, gap=None):
    if gap is None:
        gap = max(2, int(round(height * 0.18)))
    w = 0
    for ch in str(text):
        if ch == " ":
            w += int(round(height * 0.35))
        elif ch in _SEG:
            w += int(round(height * 0.55))
        else:
            w += int(round(height * 0.45))
        w += gap
    return max(0, w - gap)
