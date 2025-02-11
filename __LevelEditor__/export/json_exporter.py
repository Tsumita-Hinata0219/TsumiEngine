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
from ..utils.transform_utils import decompose_transform
from ..properties.object_properties import get_category_data
from ..properties.collider_props import get_collider_data


class MyAddon_json_exporter(bpy.types.Operator, bpy_extras.io_utils.ExportHelper):
    bl_idname = "myaddon.json_exporter"
    bl_label = "シーン出力"
    bl_description = "シーン情報をExportします"
    filename_ext = ".json"

    # ---- Export to JSON ----
    def parse_scene_recursive_json(self, data_parent, obj):
        """シーンデータを再帰的にJSON形式で書き出す"""
        obj_data = {
            "type": obj.type,
            "name": obj.name,
            "transform": decompose_transform(obj),
            "collider": get_collider_data(obj),
            "category": get_category_data(obj),
            "children": [],
        }
        data_parent.append(obj_data)

        for child in obj.children:
            self.parse_scene_recursive_json(obj_data["children"], child)

    # ---- Export Methods ----
    def export_json(self):
        """シーン情報をJSON形式でエクスポート"""
        scene_data = {"name": "scene", "objects": []}

        for obj in bpy.context.scene.objects:
            if not obj.parent:
                self.parse_scene_recursive_json(scene_data["objects"], obj)

        json_text = json.dumps(scene_data, ensure_ascii=False, indent=4)

        with open(self.filepath, "wt", encoding="utf-8") as file:
            file.write(json_text)

    def export_text(self):
        """シーン情報をテキスト形式でエクスポート"""
        with open(self.filepath, "wt", encoding="utf-8") as file:
            file.write("SCENE\n")
            for obj in bpy.context.scene.objects:
                if not obj.parent:
                    self.parse_scene_recursive(file, obj, 0)

    # ---- Operator Execution ----
    def execute(self, context):
        """エクスポート処理の実行"""
        self.export_json()
        self.report({'INFO'}, "シーン情報をExportしました")
        return {'FINISHED'}
