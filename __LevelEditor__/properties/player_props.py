import bpy
from bpy.props import StringProperty, EnumProperty, IntProperty, FloatProperty, FloatVectorProperty


# ──────────── プレイヤープロパティ
class Player_Props(bpy.types.PropertyGroup):
    pass


# ──────────── プレイヤープロパティを描画
def draw_player_properties(layout, props):
    pass


# ──────────── Json出力するプレイヤー情報を取得
def get_player_data(category_data, obj):
    """PLAYERカテゴリのデータを追加"""
    pass