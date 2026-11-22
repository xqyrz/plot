# -*- coding: utf-8 -*-
"""生成棋盤格標定板（相機內參 / 畸變標定）——OpenGL 離屏渲染。

方格邊長以像素計，所以輸出圖與 OpenCV 的 findChessboardCornersSB 完美對齊：
內角點數 = (cols-1, rows-1)。

範例
----
    python gen_chessboard.py                              # 10x7 方格, 邊長 120px
    python gen_chessboard.py --cols 12 --rows 9 --square-px 80
    python gen_chessboard.py --invert --bits 16            # 左上角改為白色
"""
import argparse
import os

import mvgl.targets as T


def main():
    ap = argparse.ArgumentParser(description="棋盤格標定板生成器（OpenGL）")
    ap.add_argument("--cols", type=int, default=10, help="橫向方格數")
    ap.add_argument("--rows", type=int, default=7, help="縱向方格數")
    ap.add_argument("--square-px", type=int, default=120, help="每個方格邊長（像素）")
    ap.add_argument("--margin", type=int, default=1, help="四周白邊寬度（以方格數計）")
    ap.add_argument("--invert", action="store_true", help="左上角方格改為白色")
    ap.add_argument("--ssaa", type=int, default=4)
    ap.add_argument("--bits", type=int, default=8, choices=[8, 16])
    ap.add_argument("--out", default="output")
    args = ap.parse_args()

    os.makedirs(args.out, exist_ok=True)
    img, meta = T.chessboard(cols=args.cols, rows=args.rows, square_px=args.square_px,
                             margin_squares=args.margin, ssaa=args.ssaa, invert=args.invert)

    name = "chessboard_%dx%d_sq%d%s.png" % (args.cols, args.rows, args.square_px,
                                            "_invert" if args.invert else "")
    path = os.path.join(args.out, name)
    T.save(img, path, bit_depth=args.bits, encode="srgb", dpi=300)
    T.save_meta(path, meta)

    print("尺寸: %dx%d px, 內角點 %dx%d" % (meta["size"][0], meta["size"][1],
                                            meta["inner_corners"][0], meta["inner_corners"][1]))
    print("每格物理尺寸若為 %.1f mm，則整板 %.1f x %.1f mm（不含白邊）"
          % (10.0, args.cols * 10.0, args.rows * 10.0))
    print("已輸出:", path)


if __name__ == "__main__":
    main()
