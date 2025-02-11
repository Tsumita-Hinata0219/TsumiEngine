import bpy
import math
import mathutils
from bpy.props import StringProperty, EnumProperty, PointerProperty, CollectionProperty, FloatProperty, FloatVectorProperty


# ──────────── コライダープロパティ
class Collider_Props(bpy.types.PropertyGroup):
    obj = bpy.types.Object
    obj.collider_type = EnumProperty(
        name="Collider Type",
        items=[
            ('NONE', "None", ""),
            ('AABB', "AABB", ""),
            ('SPHERE', "Sphere", "")
        ],
        default='NONE'
    )
    obj.collider_center = FloatVectorProperty(
        name="Center",
        size=3,
        default=(0.0, 0.0, 0.0)
    )
    obj.collider_size = FloatVectorProperty(
        name="Size",
        size=3,
        default=(2.0, 2.0, 2.0)
    )
    obj.collider_radius = FloatProperty(
        name="Radius",
        default=1.0
    )

# ──────────── コライダープロパティを描画
def draw_collider_properties(layout, obj):
    layout.prop(obj, "collider_type", text="")
    layout.prop(obj, "is_trigger", text="Is Trigger")
    
    # コライダータイプに基づいてプロパティを描画
    if obj.collider_type in {'AABB', 'OBB'}:
        # AABB/OBB共通プロパティ
        layout.prop(obj, "collider_center", text="中心座標")
        layout.prop(obj, "collider_size", text="サイズ")
    elif obj.collider_type == 'SPHERE':
        # Sphere用プロパティ
        layout.prop(obj, "collider_center", text="中心座標")
        row = layout.row(align=True)
        row.label(text="半径")
        row.prop(obj, "collider_radius", text="")
    else:
        layout.label(text="選択されたコライダータイプはありません")
    
    layout.separator()


# ──────────── Json出力するコライダー情報を取得
def get_collider_data(obj):
        collider_type = obj.collider_type
        collider_center = list(obj.get("collider_center", mathutils.Vector((0, 0, 0))))
        collider_size = list(obj.get("collider_size", mathutils.Vector((2, 2, 2))))
        collider_radius = obj.get("collider_radius", 1)

        # コライダーの情報を個別に取得
        collider_data = {}
        collider_data["type"] = collider_type  # "type" を文字列で格納

        # コライダータイプに基づいて情報を追加
        if collider_type == "AABB" or collider_type == "OBB":
            collider_data["center"] = collider_center
            collider_data["size"] = collider_size
        elif collider_type == "SPHERE":
            collider_data["center"] = collider_center
            collider_data["radius"] = collider_radius

        return collider_data