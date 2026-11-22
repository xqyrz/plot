#!/usr/bin/env python3
"""极简 PNG 读写（只依赖 numpy），避免为了出图再装 opencv / pillow。

写出支持：
  - 8bit 灰度 (H,W)
  - 8bit RGB  (H,W,3)
  - 16bit 灰度 (H,W) uint16
  - 可选写入 pHYs(DPI)，打印时能保持物理尺寸

读入支持：
  - 8bit、非交错的灰度(0) / RGB(2) / RGBA(6)
  - 5 种 filter 全部支持（用于把任意 PNG 转成 Bayer RAW）
"""

import struct
import zlib

import numpy as np

# 常用纸张尺寸（mm）
PAGE_MM = {
    "a4": (210, 297),
    "a3": (297, 420),
    "letter": (215.9, 279.4),
}


def mm2px(mm, dpi):
    """毫米 -> 像素"""
    return int(round(mm / 25.4 * dpi))


def _chunk(tag, data):
    return (
        tag
        + struct.pack(">I", len(data))
        + data
        + struct.pack(">I", zlib.crc32(tag + data) & 0xFFFFFFFF)
    )


def write_png(path, arr, dpi=None):
    """把 numpy 数组写成 PNG。

    arr: uint8 (H,W) 灰度 / uint8 (H,W,3) RGB / uint16 (H,W) 16bit 灰度
    dpi: 写入 pHYs，打印时按此分辨率换算物理尺寸
    """
    a = np.asarray(arr)
    if a.ndim != 2 and not (a.ndim == 3 and a.shape[2] == 3):
        raise ValueError("只支持 (H,W) 或 (H,W,3)")

    h, w = a.shape[:2]

    if a.ndim == 3:
        depth, ctype = 8, 2
    elif a.dtype == np.uint16:
        depth, ctype = 16, 0
    else:
        depth, ctype = 8, 0

    def row_bytes(row):
        if depth == 16:
            return row.astype(">u2").tobytes()
        return np.ascontiguousarray(row, dtype=np.uint8).tobytes()

    raw = b"".join(b"\x00" + row_bytes(a[y]) for y in range(h))

    out = [b"\x89PNG\r\n\x1a\n"]
    out.append(_chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, depth, ctype, 0, 0, 0)))
    if dpi:
        ppm = int(round(dpi / 0.0254))
        out.append(_chunk(b"pHYs", struct.pack(">IIB", ppm, ppm, 1)))
    out.append(_chunk(b"IDAT", zlib.compress(raw, 6)))
    out.append(_chunk(b"IEND", b""))

    with open(path, "wb") as f:
        f.write(b"".join(out))
    return path


def read_png(path):
    """读 8bit PNG（灰度/RGB/RGBA），返回 (H,W) 或 (H,W,C) 的 uint8"""
    with open(path, "rb") as f:
        data = f.read()

    if data[:8] != b"\x89PNG\r\n\x1a\n":
        raise ValueError("不是 PNG 文件: %s" % path)

    pos, idat, ihdr = 8, b"", None
    while pos < len(data):
        ln = struct.unpack(">I", data[pos:pos + 4])[0]
        tag = data[pos + 4:pos + 8]
        body = data[pos + 8:pos + 8 + ln]
        pos += 12 + ln
        if tag == b"IHDR":
            ihdr = struct.unpack(">IIBBBBB", body)
        elif tag == b"IDAT":
            idat += body
        elif tag == b"IEND":
            break

    if ihdr is None:
        raise ValueError("PNG 缺少 IHDR")
    w, h, depth, ctype, comp, filt, inter = ihdr
    if depth != 8 or inter != 0:
        raise ValueError("只支持 8bit 非交错 PNG（depth=%d interlace=%d）" % (depth, inter))
    if ctype not in (0, 2, 6):
        raise ValueError("只支持灰度/RGB/RGBA（color type=%d）" % ctype)

    nch = {0: 1, 2: 3, 6: 4}[ctype]
    stride = w * nch
    raw = zlib.decompress(idat)

    out = np.empty((h, stride), dtype=np.uint8)
    prev = np.zeros(stride, dtype=np.int32)
    p = 0
    for y in range(h):
        ft = raw[p]
        p += 1
        line = np.frombuffer(raw[p:p + stride], dtype=np.uint8).astype(np.int32)
        p += stride

        if ft == 0:
            cur = line
        elif ft == 1:  # Sub
            cur = line.copy()
            for i in range(nch, stride):
                cur[i] = (cur[i] + cur[i - nch]) & 0xFF
        elif ft == 2:  # Up
            cur = (line + prev) & 0xFF
        elif ft == 3:  # Average
            cur = line.copy()
            for i in range(stride):
                left = cur[i - nch] if i >= nch else 0
                cur[i] = (cur[i] + ((left + prev[i]) >> 1)) & 0xFF
        elif ft == 4:  # Paeth
            cur = line.copy()
            for i in range(stride):
                a3 = cur[i - nch] if i >= nch else 0
                b3 = prev[i]
                c3 = prev[i - nch] if i >= nch else 0
                pa, pb, pc = abs(b3 - c3), abs(a3 - c3), abs(a3 + b3 - 2 * c3)
                pr = a3 if (pa <= pb and pa <= pc) else (b3 if pb <= pc else c3)
                cur[i] = (cur[i] + pr) & 0xFF
        else:
            raise ValueError("未知 filter=%d" % ft)

        out[y] = cur.astype(np.uint8)
        prev = cur

    img = out.reshape(h, w, nch)
    return img if nch > 1 else img[:, :, 0]


def center_on_page(img, page="a4", dpi=300, bg=255):
    """把图案居中放到指定纸张上，返回新数组"""
    pw_mm, ph_mm = PAGE_MM[page.lower()]
    pw, ph = mm2px(pw_mm, dpi), mm2px(ph_mm, dpi)
    if img.ndim == 2:
        canvas = np.full((ph, pw), bg, dtype=np.uint8)
    else:
        canvas = np.full((ph, pw, img.shape[2]), bg, dtype=np.uint8)
    h, w = img.shape[:2]
    if h > ph or w > pw:
        raise ValueError("图案 %.0fx%.0fmm 放不进 %s" % (w / dpi * 25.4, h / dpi * 25.4, page))
    y0, x0 = (ph - h) // 2, (pw - w) // 2
    canvas[y0:y0 + h, x0:x0 + w] = img
    return canvas


def ensure_dir(path):
    import os

    os.makedirs(os.path.dirname(os.path.abspath(path)), exist_ok=True)
    return path
