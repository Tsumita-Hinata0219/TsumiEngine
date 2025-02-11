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


# ──────────── モジュールのインポート
from .. import bl_info
from ..export.json_exporter import MyAddon_json_exporter
from ..spawn.spawn import MYADDON_OT_spawn_import_symbol, MYADDON_OT_spawn_create_symbol


# ──────────── 拡張メニュー
class MyAddon_MyMenu(bpy.types.Menu):
    bl_idname = "myaddon_mymenu"
    bl_label = "MyMenu"
    bl_description = "拡張メニュー by " + bl_info["author"]

    def draw(self, context):
        self.layout.operator("wm.url_open_preset", text="Manual", icon='HELP')
        self.layout.operator(MyAddon_json_exporter.bl_idname, text=MyAddon_json_exporter.bl_label)
        self.layout.operator(MYADDON_OT_spawn_import_symbol.bl_idname, text=MYADDON_OT_spawn_import_symbol.bl_label)
        self.layout.operator(MYADDON_OT_spawn_create_symbol.bl_idname, text=MYADDON_OT_spawn_create_symbol.bl_label)

    def submenu(self, context):
        self.layout.menu(MyAddon_MyMenu.bl_idname)

    # ──────────── MyMenuにシーン出力の項目を追加
    def menu_func_export(self, context):
        self.layout.operator(MyAddon_json_exporter.bl_idname, text="Export Scene (.json)")

    # ──────────── SpawnPointの項目を追加
    def menu_func_spawn(self, context):
        self.layout.operator(MYADDON_OT_spawn_import_symbol.bl_idname, text="Spawn")

    # ──────────── SpawnSymbol作成の項目を追加
    def menu_func_spawnSymbol(self, context):
        self.layout.operator(MYADDON_OT_spawn_import_symbol.bl_idname, text="Create SpawnSymbol")



# ──────────── マイメニューの初期化と削除
def init_myMenu():
    # メニューに項目を追加
    bpy.types.TOPBAR_MT_editor_menus.append(MyAddon_MyMenu.submenu)
    bpy.types.TOPBAR_MT_file_export.append(MyAddon_MyMenu.menu_func_export)
    bpy.types.TOPBAR_MT_file_export.append(MyAddon_MyMenu.menu_func_spawn)
    bpy.types.TOPBAR_MT_file_export.append(MyAddon_MyMenu.menu_func_spawnSymbol)

def clear_myMenu():
    # メニューから項目を削除
    bpy.types.TOPBAR_MT_editor_menus.remove(MyAddon_MyMenu.submenu)
    bpy.types.TOPBAR_MT_file_export.remove(MyAddon_MyMenu.menu_func_export)
    bpy.types.TOPBAR_MT_file_export.remove(MyAddon_MyMenu.menu_func_spawn)
    bpy.types.TOPBAR_MT_file_export.remove(MyAddon_MyMenu.menu_func_spawnSymbol)