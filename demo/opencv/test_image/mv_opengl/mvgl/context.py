# -*- coding: utf-8 -*-
"""離屏 OpenGL 渲染核心（moderngl，不開視窗，純 GPU 光柵化）。

設計要點
--------
* 使用 fullscreen triangle，圖案幾何完全在 fragment shader 中以解析式生成，
  因此解析度任意、邊緣相位精確（對標定靶非常關鍵）。
* 先以 ssaa 倍超取樣渲染到 float32 FBO，再盒式降採樣，
  得到接近「理想標靶」的抗鋸齒邊緣，而不是被平滑糊掉的邊。
* 一律輸出線性光（linear RGB），轉 sRGB / 位元量化交給下游處理。
"""
import numpy as np

try:
    import moderngl
except ImportError as e:  # pragma: no cover
    raise SystemExit("需要 moderngl：pip install moderngl") from e

_FULLSCREEN_VS = """#version 330 core
void main() {
    // 不帶 VBO，用 gl_VertexID 直接鋪一個覆蓋整個視口的大三角形
    vec2 p = vec2(float((gl_VertexID << 1) & 2), float(gl_VertexID & 2));
    gl_Position = vec4(p * 2.0 - 1.0, 0.0, 1.0);
}
"""


class GLRenderer:
    """單例式離屏渲染器（一個進程內共用一個 GL context）。"""

    def __init__(self, require: int = 330):
        self.ctx = moderngl.create_standalone_context(require=require)
        self.renderer_name = self.ctx.info.get("GL_RENDERER", "unknown")
        self._cache = {}

    def _program(self, fs_src: str):
        key = hash(fs_src)
        if key not in self._cache:
            self._cache[key] = self.ctx.program(vertex_shader=_FULLSCREEN_VS, fragment_shader=fs_src)
        return self._cache[key]

    @staticmethod
    def _set(prog, name, value):
        u = prog[name]
        if isinstance(value, np.ndarray):
            data = np.ascontiguousarray(value, dtype="f4")
            u.write(data.tobytes())
        elif isinstance(value, (tuple, list)) and len(value) > 4:
            u.write(np.ascontiguousarray(value, dtype="f4").tobytes())
        else:
            u.value = value

    def render(self, fs_src, uniforms=None, size=(1024, 1024), ssaa=4):
        """渲染並回傳 (H,W,3) float32 線性影像，y 軸向下（圖像座標）。"""
        w, h = int(size[0]), int(size[1])
        W, H = w * ssaa, h * ssaa

        tex = self.ctx.texture((W, H), 4, dtype="f4")
        fbo = self.ctx.framebuffer(color_attachments=[tex])
        try:
            prog = self._program(fs_src)
            # u_res / u_ssaa 由渲染器權威設定：shader 內一律以「最終圖像像素」為座標單位
            caller = dict(uniforms or {})
            caller.pop("u_res", None)
            caller.pop("u_ssaa", None)
            caller["u_res"] = (float(W), float(H))
            caller["u_ssaa"] = float(ssaa)
            for k, v in caller.items():
                try:
                    self._set(prog, k, v)
                except KeyError:
                    pass  # shader 中被最佳化掉的 uniform
                except Exception as e:
                    raise RuntimeError("設定 uniform %s 失敗: %s" % (k, e))

            fbo.use()
            fbo.clear(0.0, 0.0, 0.0, 1.0)
            vao = self.ctx.vertex_array(prog, [])
            vao.render(moderngl.TRIANGLES, vertices=3)
            vao.release()

            raw = fbo.read(components=3, dtype="f4")
            img = np.frombuffer(raw, dtype="f4").reshape(H, W, 3)[::-1]  # GL 是 y 向上
        finally:
            fbo.release()
            tex.release()

        if ssaa > 1:
            img = img.reshape(h, ssaa, w, ssaa, 3).mean(axis=(1, 3))
        return np.ascontiguousarray(img)
