import bpy
from bpy.props import StringProperty, EnumProperty, PointerProperty, CollectionProperty, FloatProperty
from gpu_extras.batch import batch_for_shader
import copy
import gpu
import gpu_extras.batch
import math
import mathutils


# ──────────── コライダー描画
class MyAddon_Draw_Collider(bpy.types.Operator):

    def draw_collider():

        objects = bpy.context.scene.objects

        # 3Dビューに登録する描画関数
        # 頂点データ
        vertices = {"pos": []}
        
        # インデックス
        indices = []

        # 現在シーンのオブジェクトリストを操作
        for obj in objects:
            # コライダータイプの取得
            collider_type = obj.collider_type

            # コライダープロパティがない or コライダータイプがNONEなら描画をスキップ
            if collider_type == 'NONE':
                continue

            # AABB コライダー
            elif collider_type == 'AABB':  # AABB
                draw_aabb(obj, vertices, indices)
            # OBB コライダー
            elif collider_type == 'OBB':  # OBB
                draw_obb(obj, vertices, indices)
            # Sphere コライダー
            elif collider_type == 'SPHERE':  # Sphere
                draw_sphere(obj, vertices, indices)

        # ビルドインのシェーダを取得
        shader = gpu.shader.from_builtin('UNIFORM_COLOR')

        # バッチを作成(引数 : シェーダ、トポロジー、頂点データ、インデックスデータ)
        batch = gpu_extras.batch.batch_for_shader(shader, "LINES", vertices, indices=indices)

        # シェーダのパラメータ設定
        color = [0.5, 1.0, 1.0, 1.0]
        shader.bind()
        shader.uniform_float("color", color)

        # 描画
        batch.draw(shader)


# ──────────── プロパティの初期化と削除
def init_collider_draw():
    # 3Dビューに描画関数を追加
    MyAddon_Draw_Collider.handle = bpy.types.SpaceView3D.draw_handler_add(MyAddon_Draw_Collider.draw_collider, (), "WINDOW", "POST_VIEW")
    

def clear_collider_draw():
    # 描画ハンドラの削除
    if MyAddon_Draw_Collider.handle is not None:
        bpy.types.SpaceView3D.draw_handler_remove(MyAddon_Draw_Collider.handle, "WINDOW")


# ──────────── プロパティの登録と解除
def register_collider_draw():
    pass

def unregister_collider_draw():
    pass


# ──────────── コライダーの描画
def draw_aabb(obj, vertices, indices):
    offsets = [
        [-0.5, -0.5, -0.5],
        [+0.5, -0.5, -0.5],
        [-0.5, +0.5, -0.5],
        [+0.5, +0.5, -0.5],
        [-0.5, -0.5, +0.5],
        [+0.5, -0.5, +0.5],
        [-0.5, +0.5, +0.5],
        [+0.5, +0.5, +0.5],
    ]

    center = mathutils.Vector(obj.collider_center)
    size = mathutils.Vector(obj.collider_size)

    for offset in offsets:
        pos = center + mathutils.Vector(offset) * size
        pos = obj.matrix_world @ pos
        vertices["pos"].append(pos)

    indices.extend([
        [0, 1], [2, 3], [0, 2], [1, 3],
        [4, 5], [6, 7], [4, 6], [5, 7],
        [0, 4], [1, 5], [2, 6], [3, 7],
    ])

def draw_obb(obj, vertices, indices):
    # Similar to draw_aabb, but include rotation transformations
    offsets = [
        [-0.5, -0.5, -0.5],
        [+0.5, -0.5, -0.5],
        [-0.5, +0.5, -0.5],
        [+0.5, +0.5, -0.5],
        [-0.5, -0.5, +0.5],
        [+0.5, -0.5, +0.5],
        [-0.5, +0.5, +0.5],
        [+0.5, +0.5, +0.5],
        ]
    
    center = mathutils.Vector(obj.collider_center)
    size = mathutils.Vector(obj.collider_size)
    rotation = obj.matrix_world.to_3x3()
    for offset in offsets:
        local_pos = mathutils.Vector(offset) * size
        pos = rotation @ local_pos + center
        pos = obj.matrix_world @ pos
        vertices["pos"].append(pos)

    start = len(vertices["pos"]) - 8
    indices.extend([
        [start + 0, start + 1], [start + 2, start + 3], [start + 0, start + 2], [start + 1, start + 3],
        [start + 4, start + 5], [start + 6, start + 7], [start + 4, start + 6], [start + 5, start + 7],
        [start + 0, start + 4], [start + 1, start + 5], [start + 2, start + 6], [start + 3, start + 7],
    ])

def draw_sphere(obj, vertices, indices):
    center = mathutils.Vector(obj.collider_center)
    radius = obj.collider_radius
    segments = 16
    rings = 8

    start = len(vertices["pos"])
    for i in range(rings + 1):
        theta = math.pi * i / rings
        for j in range(segments):
            phi = 2 * math.pi * j / segments
            x = radius * math.sin(theta) * math.cos(phi)
            y = radius * math.sin(theta) * math.sin(phi)
            z = radius * math.cos(theta)
            pos = center + mathutils.Vector((x, y, z))
            pos = obj.matrix_world @ pos
            vertices["pos"].append(pos)

    for i in range(rings):
        for j in range(segments):
            next_j = (j + 1) % segments
            indices.append([start + i * segments + j, start + i * segments + next_j])
            indices.append([start + i * segments + j, start + (i + 1) * segments + j])
            indices.append([start + i * segments + next_j, start + (i + 1) * segments + next_j])
