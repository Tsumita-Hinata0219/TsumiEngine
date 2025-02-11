import bpy
import mathutils
from bpy.props import StringProperty, EnumProperty, BoolProperty, IntProperty, FloatProperty, FloatVectorProperty


# ──────────── プレイヤープロパティ
class Disabled_Props(bpy.types.PropertyGroup):
    obj = bpy.types.Object
    obj.object_disabled = BoolProperty(
        name="Disabled",
        description="Object Disabled",
        default=False
    )


# ──────────── プレイヤープロパティを描画
def draw_disabled_properties(layout, obj):
    # Tilt Body
    layout.prop(obj, "object_disabled", text="Disabled")


# ──────────── Json出力するプレイヤー情報を取得
def get_disabled_data(category_data, obj):
    """PLAYERカテゴリのデータを追加"""
    pass