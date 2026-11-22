# mvgl — OpenGL 工業視覺 / 機器視覺標靶生成工具

用 GPU（OpenGL 3.3 Core，離屏 FBO）解析式生成機器視覺常用測試圖：24 色卡、棋盤格、非對稱圓點陣列、西門子星、階梯灰卡、斜邊靶（MTF）、區域板、平場、隨機點陣，以及可指定 CFA / 位深的 Bayer **RAW** 圖。

## 為什麼用 OpenGL 而不是 numpy/PIL 畫圖

| 做法 | 問題 |
|---|---|
| PIL / numpy 逐像素 | 大圖慢；圓、斜邊、扇形靠光柵化公式容易走樣 |
| **OpenGL fragment shader（本專案）** | 圖案是**解析式**的：給定像素座標直接算出顏色，因此解析度任意、邊緣相位精確到亞像素、幾何完全無離散化誤差 |

關鍵設計：

- **解析式圖案**：棋盤格、圓點、扇形、斜邊都在 shader 裡用 `floor`/`fract`/`atan2` 算，不存在「先畫小圖再放大」的失真。
- **座標統一**：shader 內一律以「最終圖像像素」為單位（`img_pos()`），超取樣倍數由 `u_ssaa` 補償，所以同一份參數在 400px 與 4000px 輸出下幾何完全一致。
- **超取樣（SSAA）**：先在 `ssaa` 倍解析度的 float32 FBO 渲染，再盒式降採樣。棋盤格、圓點邊緣因此是乾淨的抗鋸齒灰階過渡，而不是糊掉的邊。
- **線性光工作流**：渲染全程 linear RGB（float32），最後才按需求做 sRGB 編碼 / 位元量化。色卡數值因此能與標稱 sRGB 值對得上（實測差 ≤1 LSB）。

## 安裝

```bash
pip install -r requirements.txt       # numpy, moderngl, Pillow
```

需要 OpenGL 3.3+ 的顯卡驅動（NVIDIA / AMD / Intel 均可）。`moderngl.create_standalone_context()` 走離屏上下文，**不需要開視窗**，可跑在無頭環境（Linux + EGL）。

## 快速開始

```bash
python gen_all.py            # 一次生成全套（約十幾秒）
python gen_all.py --quick    # 小尺寸，只驗證環境
```

單獨生成：

```bash
python gen_colorchecker24.py --patch-px 400 --labels     # 24 色卡（1280×1920），附編號預覽
python gen_chessboard.py --cols 10 --rows 7 --square-px 140
python gen_chessboard.py --cols 12 --rows 9 --square-px 100 --invert --bits 16
python gen_targets.py --target circle_grid --cols 11 --rows 8 --spacing 64
python gen_targets.py --target all --size 1800
python gen_raw.py --target colorchecker --bits 12 --cfa RGGB --wb 1.9 1.0 1.55 --exposure 0.5
```

所有腳本都輸出到 `--out`（預設 `output/`），並在 PNG 旁邊寫一份同名 `.json` 記錄幾何/色彩參數——量測腳本可以直接讀，不必再猜參數。

## 檔案結構

```
mvgl/
  context.py   GL 離屏渲染核心（FBO + 超取樣 + 盒式降採樣）
  shaders.py   全部圖案的 GLSL fragment shader
  targets.py   高階 API：算參數 → 渲染 → 回傳線性影像 + 元資料
  sensor.py    Bayer 馬賽克、暗角、散粒/讀出噪聲、位元量化、雙線性去馬賽克
  color.py     sRGB ↔ 線性 轉換、24 色卡標稱值
  pngio.py     自帶 PNG 寫入器（8/16bit、RGB/灰階，16bit RGB 不依賴 PIL）
gen_colorchecker24.py   24 色卡
gen_chessboard.py       棋盤格標定板
gen_targets.py          圓點陣列 / 西門子星 / 灰階楔 / 斜邊 / 區域板 / 平場 / 隨機點
gen_raw.py              Bayer RAW 生成
gen_all.py              全套批次
```

## 各標靶要點

**24 色卡**（`colorchecker24_*.png`）
4×6 佈局，色塊填的是 X-Rite ColorChecker Classic 的標準 sRGB 標稱值（轉線性後渲染）。輸出兩份：`_srgb8.png`（直接看/列印）與 `_linear16.png`（16bit 線性，給色彩校正/RAW 模擬用）。

**棋盤格**（`chessboard_*`）
內角點數 = (cols-1, rows-1)，例如 10×7 方格 → 9×6 內角點，直接餵 `cv2.findChessboardCornersSB`。四周留白寬度以「方格數」計，方便列印後裁切。

**非對稱圓點陣列**（`circle_grid_*`）
奇數列橫向偏移半個間距，對應 `cv2.findCirclesGrid(..., CALIB_CB_ASYMMETRIC_GRID)`；圓點比棋盤格更抗離焦與透視。

**西門子星**（`siemens_star_*`）
72 扇形，用來看對焦、極限解析度與鏡頭 MTF 的截止頻率。

**階梯灰卡**（`gray_wedge_*`）
預設 21 級、**級值按 sRGB 編碼等分**（相機噪聲/SNR 評測的常用定義）；`--linear-steps` 改成線性等分。

**斜邊靶**（`slanted_edge_*`）
白底上旋轉 5° 的黑方塊，四條邊都能直接做 ISO 12233 斜邊法 SFR/MTF 計算。

**區域板 / 平場 / 隨機點**
區域板看解析度極限與摩爾紋；平場做暗角與壞點校正；隨機點看特徵點密度與幾何畸變。

## RAW 圖

`gen_raw.py` 把「理想線性場景」走一遍感測器模型：

```
GPU 線性渲染 → 白平衡增益 → 曝光 → (可選)暗角
            → Bayer 馬賽克 → 散粒噪聲(泊松近似) + 讀出噪聲
            → 黑電平/滿阱 → 位元量化 → .raw
```

輸出三件套：

- `*_bayer{CFA}_{bits}bits.raw` — 裸二進位 `uint16` little-endian，**無標頭**，`np.fromfile(path, dtype='<u2').reshape(h, w)`
- `*.json` — `cfa`、`bit_depth`、`black_level`、`white_level`、`wb_gains`、`full_well_e`、`read_noise_e`、`vignetting`、`seed`
- `*_preview.png` — 雙線性去馬賽克 + 還原 WB 後的預覽（**只是給眼睛看的**，不是 ISP 成品）

支援 `RGGB / BGGR / GRBG / GBRG`、8/10/12/14/16 bit、`--gain`（類比增益，會讓高光更容易飽和，可复現 ISO 拉高後的裁切行為）。

若需要 DNG，可用 `rawpy`/`dnglab` 依 json 中的參數轉換；本工具只給最乾淨的裸 RAW + 元資料。

## 精度自檢（生成時自動跑）

- 24 色卡：色塊中心還原值與標稱 sRGB 值差 **≤1 LSB**
- RAW 往返：12bit、無噪聲條件下，寫入→讀回→去馬賽克，最大線性誤差 **0.0001**（約 0.4 LSB，即量化極限）

## 列印與實物建議

- PNG 已寫 `pHYs`（預設 300 dpi），按 100% 列印即可保證方格/圓點尺寸。
- 黑白靶用**霧面啞光紙**或陶瓷/鋁基板，避免鏡面反射與紙張紋理；黑塊反射率建議 <5%，白塊 >85%。
- 色卡是「標稱值」而非你手上那張卡的實測值；做嚴格色彩校正時仍應用分光光度計實測自己的色卡。

## 擴展新圖案

1. 在 `mvgl/shaders.py` 加一段繼承 `COMMON` 的 fragment shader，用 `img_pos()` / `img_uv()` 取座標；
2. 在 `mvgl/targets.py` 加一個函式，算好尺寸與 uniform 後呼叫 `renderer().render(...)`；
3. 在 `gen_targets.py` 的 `build()` 掛一個分支。幾何一律用「最終像素」表述，超取樣自動處理。
