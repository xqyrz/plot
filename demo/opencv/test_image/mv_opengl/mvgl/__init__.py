# -*- coding: utf-8 -*-
"""mvgl — OpenGL 工業視覺標靶生成庫。"""
from .context import GLRenderer
from . import shaders, targets, sensor, pngio, color

__all__ = ["GLRenderer", "shaders", "targets", "sensor", "pngio", "color"]
__version__ = "1.0.0"
