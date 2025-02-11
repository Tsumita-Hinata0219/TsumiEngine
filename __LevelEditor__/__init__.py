import bpy
import bpy_extras
import gpu
import gpu_extras.batch
import copy
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


bl_info = {
    "name": "My_Addon",
    "author": "Hinata Tsumita",
    "version": (1, 0),
    "blender": (4, 1, 0),
    "location": "",
    "description": "マイアドオン",
    "warning": "",
    "wiki_url": "",
    "tracker_url": "",
    "category": "Object",
}


# ──────────── モジュールのインポート
from .utils.registration import register_classes, unregister_classes
from .export.json_exporter import MyAddon_json_exporter
from .ui.MyMenu import (
    MyAddon_MyMenu,
    init_myMenu,
    clear_myMenu,
)
from .spawn.spawn import MYADDON_OT_spawn_import_symbol
from .draw.draw_collider import (
    init_collider_draw,
    clear_collider_draw,
)
from .draw.draw_enemy_move_prediction import (
    init_prediction_draw,
    clear_prediction_draw
)
from .properties.object_properties import (
    init_object_properties,
    clear_object_properties,
    register_object_properties,
    unregister_object_properties,
)



# ──────────── クラス登録リスト
classes = [
    MyAddon_MyMenu,
    MyAddon_json_exporter,
    MYADDON_OT_spawn_import_symbol,
]



# ──────────── プロパティの初期化
def Init_Props():
    init_object_properties()
    init_collider_draw()
    init_prediction_draw()
    init_myMenu()
    


# ──────────── プロパティ解放
def clear_Props():
    clear_object_properties()
    clear_collider_draw()
    clear_prediction_draw()
    clear_myMenu()
    

# ──────────── レベルエディター有効化
def register():
    
    # クラスを登録
    register_classes(classes)
    # プロパティを登録
    register_object_properties()

    # プロパティの初期化
    Init_Props()

    print("アドオン : 「レベルエディタ」が有効化されました。")


# ──────────── レベルエディター無効化
def unregister():

    # プロパティを削除
    clear_Props()

    # クラスを登録解除
    unregister_classes(classes)
    # プロパティを登録解除
    unregister_object_properties()
    
    print("アドオン : 「レベルエディタ」が無効化されました。")


if __name__ == "__main__":
    register()
