# -*- coding: utf-8 -*-
"""一次生成全套標靶（含 RAW 樣本），輸出到 ./output。

    python gen_all.py
    python gen_all.py --quick      # 小尺寸，只為驗證環境
"""
import argparse
import os
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))

QUICK = [
    ["gen_colorchecker24.py", "--patch-px", "80", "--ssaa", "2"],
    ["gen_chessboard.py", "--cols", "6", "--rows", "4", "--square-px", "60", "--ssaa", "2"],
    ["gen_targets.py", "--target", "all", "--size", "400", "--steps", "11",
     "--patch-px", "40", "--height", "120", "--width", "400", "--ssaa", "2"],
    ["gen_raw.py", "--target", "colorchecker", "--bits", "12", "--size", "400", "600"],
]

FULL = [
    ["gen_colorchecker24.py", "--patch-px", "400", "--labels"],
    ["gen_chessboard.py", "--cols", "10", "--rows", "7", "--square-px", "140"],
    ["gen_chessboard.py", "--cols", "12", "--rows", "9", "--square-px", "100", "--invert", "--bits", "16"],
    ["gen_targets.py", "--target", "all", "--size", "1800"],
    ["gen_raw.py", "--target", "colorchecker", "--bits", "12", "--cfa", "RGGB",
     "--wb", "1.9", "1.0", "1.55", "--exposure", "0.5", "--vignette", "0.25",
     "--size", "2048", "3072"],
    ["gen_raw.py", "--target", "chessboard", "--bits", "10", "--cfa", "GRBG", "--seed", "3"],
]


def run(cmds, out):
    for c in cmds:
        cmd = [sys.executable] + c + ["--out", out]
        print("→", " ".join(c))
        subprocess.run(cmd, cwd=HERE, check=True)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--quick", action="store_true")
    ap.add_argument("--out", default="output")
    args = ap.parse_args()
    run(QUICK if args.quick else FULL, args.out)
    print("\n完成，檔案在:", os.path.join(HERE, args.out))


if __name__ == "__main__":
    main()
