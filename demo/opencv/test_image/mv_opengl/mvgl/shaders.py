# -*- coding: utf-8 -*-
"""所有圖案的 GLSL fragment shader。每個圖案都在像素空間解析式生成。"""

# 共用片段：把 gl_FragCoord 轉成「圖像座標」（y 向下、左上原點、以最終圖像像素計）
COMMON = """
#version 330 core
uniform vec2  u_res;    // 帧缓冲实际分辨率（含超取样）
uniform float u_ssaa;   // 超取样倍数
out vec4 f_color;

vec2 img_size() { return u_res / u_ssaa; }

vec2 img_pos() {           // 最终图像像素坐标，左上为原点、y 向下
    vec2 p = gl_FragCoord.xy / u_ssaa;
    p.y = img_size().y - p.y;
    return p;
}

vec2 img_uv() { return img_pos() / img_size(); }

float srgb2lin(float c) {
    return c <= 0.04045 ? c / 12.92 : pow((c + 0.055) / 1.055, 2.4);
}
"""
# ── 24 色卡 ────────────────────────────────────────────────
COLORCHECKER = COMMON + """
uniform vec3  u_patches[24];   // 線性 RGB
uniform vec2  u_grid;          // (4, 6)
uniform float u_pad;           // 色塊內縮（相對單元邊長）
uniform vec3  u_card;          // 卡紙/邊框顏色（線性）
uniform vec3  u_frame;         // 色塊之間的分隔線顏色

void main() {
    vec2 uv = img_uv();
    vec2 g  = uv * u_grid;
    ivec2 c = ivec2(floor(g));
    vec2 f  = fract(g);                     // 單元內 0..1
    int idx = clamp(c.y * int(u_grid.x) + c.x, 0, 23);

    vec3 col = u_card;
    // 單元內縮後才是色塊
    if (f.x > u_pad && f.x < 1.0 - u_pad && f.y > u_pad && f.y < 1.0 - u_pad)
        col = u_patches[idx];

    f_color = vec4(col, 1.0);
}
"""

# ── 棋盤格 ────────────────────────────────────────────────
CHESSBOARD = COMMON + """
uniform vec2  u_cells;      // (橫向方格數, 縱向方格數)
uniform vec2  u_margin;     // 白邊占全圖比例 (x, y)
uniform float u_invert;     // 0: 左上黑  1: 左上白
uniform float u_bg;         // 白邊亮度（線性）

void main() {
    vec2 uv = img_uv();
    vec2 m  = u_margin;

    float bg = u_bg;
    if (uv.x >= m.x && uv.x <= 1.0 - m.x && uv.y >= m.y && uv.y <= 1.0 - m.y) {
        vec2 s = (uv - m) / (1.0 - 2.0 * m) * u_cells;
        float p = mod(floor(s.x) + floor(s.y), 2.0);
        if (u_invert > 0.5) p = 1.0 - p;    // p=1 -> 白
        bg = p;
    }
    f_color = vec4(vec3(bg), 1.0);
}
"""

# ── 非對稱圓點陣列（OpenCV findCirclesGrid ASYMMETRIC_GRID 用） ──
CIRCLE_GRID = COMMON + """
uniform vec2  u_count;     // (每列圓點數, 列數)
uniform float u_spacing;   // 相鄰圓心間距（像素）
uniform float u_radius;    // 圓半徑（像素）
uniform vec2  u_origin;    // 第一個圓心（像素，圖像座標）
uniform float u_stagger;   // 奇數列橫向偏移（間距倍數，典型 0.5）
uniform float u_bg;        // 背景亮度

void main() {
    vec2 p = img_pos();
    float d = 1e9;
    int nx = int(u_count.x), ny = int(u_count.y);
    for (int j = 0; j < 64; j++) {
        if (j >= ny) break;
        float off = mod(float(j), 2.0) * u_stagger;
        for (int i = 0; i < 64; i++) {
            if (i >= nx) break;
            vec2 c = u_origin + vec2((float(i) + off) * u_spacing, float(j) * u_spacing);
            d = min(d, length(p - c) - u_radius);
        }
    }
    f_color = vec4(vec3(d <= 0.0 ? 0.0 : u_bg), 1.0);
}
"""

# ── 西門子星（對焦 / 極限解析度） ────────────────────────
SIEMENS_STAR = COMMON + """
uniform float u_spokes;    // 扇形數（偶數較好）
uniform vec2  u_center;
uniform float u_radius;
uniform float u_bg;

void main() {
    vec2 p = img_pos() - u_center;
    p.y = -p.y;
    float r = length(p);
    float a = atan(p.y, p.x);
    float sect = 6.28318530718 / u_spokes;
    float k = mod(floor((a + 3.14159265) / sect), 2.0);
    float v = (r < u_radius) ? k : u_bg;
    f_color = vec4(vec3(v), 1.0);
}
"""

# ── 階梯灰卡 ────────────────────────────────
GRAY_WEDGE = COMMON + """
uniform float u_steps;     // 級數
uniform float u_srgb;      // 1: 級值以 sRGB 編碼定義（相機感測器評測常用）
uniform float u_vertical;  // 1: 縱向排列

void main() {
    vec2 uv = img_uv();
    float t = u_vertical > 0.5 ? uv.y : uv.x;
    float i = floor(t * u_steps);
    float v = clamp(i / (u_steps - 1.0), 0.0, 1.0);
    if (u_srgb > 0.5) v = srgb2lin(v);
    f_color = vec4(vec3(v), 1.0);
}
"""

# ── 斜邊靶（MTF / SFR）：白底上一個旋轉 5° 的黑方塊 ─────────
SLANTED_EDGE = COMMON + """
uniform float u_angle;     // 方塊旋轉角（度，典型 5°~7°）
uniform float u_half;      // 方塊半邊長（相對 min(w,h) 的比例）

void main() {
    vec2 p = img_pos() - img_size() * 0.5;
    float a = radians(u_angle);
    // 旋轉回方塊自身座標
    vec2 r = vec2(p.x * cos(a) + p.y * sin(a),
                  -p.x * sin(a) + p.y * cos(a));
    float s = u_half * min(img_size().x, img_size().y);
    float v = (abs(r.x) < s && abs(r.y) < s) ? 0.0 : 1.0;
    f_color = vec4(vec3(v), 1.0);
}
"""

# ── 區域板 / 啁啾（解析度與摩爾紋測試） ───────────────────
ZONE_PLATE = COMMON + """
uniform float u_k;       // 相位係數：頻率隨半徑平方增加
uniform vec2  u_center;
uniform float u_bg;

void main() {
    vec2 p = (img_pos() - u_center) / img_size().y;
    float r2 = dot(p, p);
    float v = 0.5 + 0.5 * cos(2.0 * 3.14159265359 * u_k * r2);
    f_color = vec4(vec3(v), 1.0);
}
"""

# ── 純色 / 平場（暗角、白平衡、壞點校正） ────────────────
FLAT_FIELD = COMMON + """
uniform vec3 u_color;
void main() { f_color = vec4(u_color, 1.0); }
"""

# ── 隨機點陣（幾何畸變 / 特徵點密度測試） ────────────────
RANDOM_DOTS = COMMON + """
uniform float u_density;   // 每平方像素密度
uniform float u_radius;
uniform float u_seed;
uniform float u_bg;

float hash21(vec2 p) {
    p = fract(p * vec2(123.34, 456.21) + u_seed);
    p += dot(p, p + 45.32);
    return fract(p.x * p.y);
}

void main() {
    vec2 p = img_pos();
    // 用最近格點抖動做「看起來隨機、但可重現」的點陣
    vec2 cell = floor(p / (u_radius * 4.0));
    float h = hash21(cell);
    vec2 c = (cell + 0.5 + 0.6 * vec2(hash21(cell + 7.1), hash21(cell + 13.7)) - 0.3) * u_radius * 4.0;
    float on = step(1.0 - u_density, h);
    float inside = (length(p - c) <= u_radius) ? 1.0 : 0.0;
    float v = on > 0.5 ? (1.0 - inside) : u_bg;
    f_color = vec4(vec3(v), 1.0);
}
"""
