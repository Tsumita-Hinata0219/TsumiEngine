import bpy
from bpy.props import StringProperty, EnumProperty, PointerProperty, CollectionProperty, FloatProperty
from ..utils.registration import register_classes, unregister_classes
from .collider_props import Collider_Props, draw_collider_properties
from .disabled_props import Disabled_Props, draw_disabled_properties
from .player_props import Player_Props, draw_player_properties, get_player_data
from .enemy_props import Enemy_Props, draw_enemy_properties, get_enemy_data


# ──────────── MeshProperyItemクラス
class Samp_PropertyItem(bpy.types.PropertyGroup):
    obj = bpy.types.Object
    obj.samp_prop_enum = bpy.props.EnumProperty(
        name="プロパティ項目",
        description="プロパティ項目",
        items=[
            ('NONE', "None", ""),
            ('PLAYER', "player", ""),
            ('ENEMY', "enemy", ""),
        ],
        default='NONE'
    )


# ──────────── パネルクラス
class Samp_PT_Custom(bpy.types.Panel):
    bl_idname = "samp_pt_custom"
    bl_label = "Samp Properties"
    bl_space_type = 'PROPERTIES'
    bl_region_type = 'WINDOW'
    bl_context = 'object'

    def draw(self, context):
        layout = self.layout
        obj = context.object  # シーンのオブジェクトを取得

        if not obj:
            layout.label(text="No active object")
            return

        # オブジェクトにプロパティを追加
        layout.label(text="オブジェクトプロパティ:")
        layout.prop(obj, "samp_prop_enum", text="")

        # 各プロパティの描画
        if obj.samp_prop_enum == 'PLAYER':
            draw_player_properties(layout, obj)
        elif obj.samp_prop_enum == 'ENEMY':
            draw_enemy_properties(layout, obj)
        else:
            layout.label(text="None")
        layout.separator()

        # コライダープロパティ
        layout.label(text="コライダープロパティ:")
        draw_collider_properties(layout, obj)
        layout.separator()


        # 無効フラグ
        layout.label(text="無効フラグ:")
        draw_disabled_properties(layout, obj)
        layout.separator()


# ──────────── クラス登録リスト
classes = [
    Samp_PropertyItem,
    Samp_PT_Custom,
    Collider_Props,
    Disabled_Props,
    Player_Props,
    Enemy_Props,
]


# ──────────── プロパティの初期化と削除
def init_object_properties():
    # サンプルプロパティをオブジェクトに登録
    bpy.types.Object.samp_property_items = PointerProperty(type=Samp_PropertyItem)
    # 各プロパティの初期化
    bpy.types.Object.collider_props = PointerProperty(type=Collider_Props)
    bpy.types.Object.disabled_props = PointerProperty(type=Disabled_Props)
    bpy.types.Object.player_props = PointerProperty(type=Player_Props)
    bpy.types.Object.enemy_props = PointerProperty(type=Enemy_Props)

def clear_object_properties():
    # サンプルプロパティを削除
    del bpy.types.Object.samp_property_items
    del bpy.types.Object.collider_props
    del bpy.types.Object.disabled_props
    del bpy.types.Object.player_props
    del bpy.types.Object.enemy_props


# ──────────── プロパティの登録と解除
def register_object_properties():
    # クラスを登録
    register_classes(classes)

def unregister_object_properties():

    # クラスを登録解除
    unregister_classes(classes)


# ──────────── Json出力するカテゴリー情報を取得
def get_category_data(obj):
    """オブジェクトのカテゴリデータを取得"""

    category_type = obj.samp_prop_enum

    # カテゴリーの情報を個別に取得
    category_data = {}
    category_data["type"] = category_type

    if category_type == "PLAYER":
        get_player_data(category_data, obj)
    elif category_type == "ENEMY":
        get_enemy_data(category_data, obj)
    elif category_type == "NONE":
        pass

    return category_data
