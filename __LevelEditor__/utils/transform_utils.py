import bpy
import bpy_extras
import gpu
import math
import mathutils
import json
from bpy.props import (
    IntProperty,
    FloatProperty,
    FloatVectorProperty,
    EnumProperty,
    BoolProperty,
)

def decompose_transform(obj):
        """トランスフォーム情報を分解"""
        trans, rot, scale = obj.matrix_local.decompose()
        return {
            "translation": list(trans),
            "rotation": [math.degrees(a) for a in rot.to_euler()],
            "scaling": list(scale),
        }