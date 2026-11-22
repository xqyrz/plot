# -*- coding: utf-8 -*-
"""極簡 PNG 寫入器：支援 8/16bit、RGB/灰階，不依賴第三方庫。

工業相機評測常用 16bit 無損圖，PIL 對 16bit RGB 支援不佳，
這裡直接按 PNG 規格（IHDR + IDAT + IEND）寫檔。
"""
import struct
import zlib

import numpy as np


def _chunk(tag: bytes, data: bytes) -> bytes:
    return (struct.pack(">I", len(data)) + tag + data
            + struct.pack(">I", zlib.crc32(tag + data) & 0xFFFFFFFF))


def write_png(path, arr, bit_depth=8, dpi=None, compress=9):
    """arr: (H,W) 灰階 或 (H,W,3) RGB，可為 uint8 / uint16 / float(0..1)。

    compress: zlib 壓縮等級 0(不壓縮/最快) ~ 9(最小)。含噪聲的大圖建議用 1~3。
    """
    arr = np.asarray(arr)
    if arr.dtype == np.float32 or arr.dtype == np.float64:
        arr = np.clip(arr, 0.0, 1.0)
        scale = 255.0 if bit_depth == 8 else 65535.0
        arr = np.round(arr * scale)
    arr = arr.astype(np.uint16 if bit_depth == 16 else np.uint8)

    if arr.ndim == 3 and arr.shape[2] >= 3:
        arr = arr[:, :, :3]
        color_type = 2
    elif arr.ndim == 2:
        arr = arr[:, :, None]
        color_type = 0
    else:
        raise ValueError("不支援的陣列形狀: %r" % (arr.shape,))

    H, W = arr.shape[:2]
    if bit_depth == 16:
        # PNG 16bit 為 big-endian per channel
        rows = arr.reshape(H, W * arr.shape[2]).astype(">u2").tobytes()
        row_len = W * arr.shape[2] * 2
    else:
        rows = arr.reshape(H, W * arr.shape[2]).astype("u1").tobytes()
        row_len = W * arr.shape[2]

    # 每行前加 filter type 0（None）
    raw = bytearray()
    for y in range(H):
        raw.append(0)
        raw += rows[y * row_len:(y + 1) * row_len]

    ihdr = struct.pack(">IIBBBBB", W, H, bit_depth, color_type, 0, 0, 0)
    extra = b""
    if dpi:
        ppm = int(round(dpi * 39.3701))
        extra = _chunk(b"pHYs", struct.pack(">IIB", ppm, ppm, 1))

    data = (b"\x89PNG\r\n\x1a\n"
            + _chunk(b"IHDR", ihdr)
            + extra
            + _chunk(b"IDAT", zlib.compress(bytes(raw), compress))
            + _chunk(b"IEND", b""))
    with open(path, "wb") as f:
        f.write(data)
    return path
