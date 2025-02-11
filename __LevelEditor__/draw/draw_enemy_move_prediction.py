import bpy
import gpu
from gpu_extras.batch import batch_for_shader
import math
import mathutils
from mathutils import Vector  # Vector型を使用


# ──────────── エネミーの移動線描画
class MyAddon_Draw_Move_Prediction(bpy.types.Operator):
    """Draw movement prediction lines"""
    
    handle = None  # 描画ハンドラ

    @staticmethod
    def draw_prediction():
        objects = bpy.context.scene.objects

        # 頂点データ
        vertices = {"pos": []}
        
        # インデックスデータ
        indices = []

        # シーン内のオブジェクトを走査
        for obj in objects:
            # 移動タイプの取得
            move_behavior = obj.enemy_move_behavior

            # NONE または STATIC はスキップ
            if move_behavior in {'NONE', 'STATIC', 'FOLLOW'}:
                continue

            if move_behavior == 'HORIZONTAL':
                draw_horizontal(obj, vertices, indices)
            elif move_behavior == 'CIRCULAR':
                draw_circular(obj, vertices, indices)

        # ビルドインのシェーダを取得
        shader = gpu.shader.from_builtin('UNIFORM_COLOR')

        # バッチ作成
        batch = batch_for_shader(shader, "LINES", vertices, indices=indices)

        # シェーダのパラメータ設定
        color = [0.5, 1.0, 0.7, 1.0]
        shader.bind()
        shader.uniform_float("color", color)

        # 描画
        batch.draw(shader)


# ──────────── 描画ハンドラの初期化と削除
def init_prediction_draw():
    MyAddon_Draw_Move_Prediction.handle = bpy.types.SpaceView3D.draw_handler_add(
        MyAddon_Draw_Move_Prediction.draw_prediction, (), "WINDOW", "POST_VIEW"
    )

def clear_prediction_draw():
    if MyAddon_Draw_Move_Prediction.handle is not None:
        bpy.types.SpaceView3D.draw_handler_remove(MyAddon_Draw_Move_Prediction.handle, "WINDOW")
        MyAddon_Draw_Move_Prediction.handle = None


# ──────────── 移動線の描画
def draw_horizontal(obj, vertices, indices):
    """Draw horizontal movement prediction using start and end points, with lines from start to object and object to end"""
    start = mathutils.Vector(obj.enemy_horizontal_start)  # 始点の座標
    end = mathutils.Vector(obj.enemy_horizontal_end)  # 終点の座標
    center = obj.location  # オブジェクトの位置（中心）

    # 始点 → オブジェクト のライン
    idx_start = len(vertices["pos"])
    vertices["pos"].append(start + center)  # 始点
    vertices["pos"].append(center)  # オブジェクト
    indices.extend([(idx_start, idx_start + 1)])

    # オブジェクト → 終点 のライン
    idx_end = len(vertices["pos"])
    vertices["pos"].append(center)  # オブジェクト
    vertices["pos"].append(end + center)  # 終点
    indices.extend([(idx_end, idx_end + 1)])

def draw_circular(obj, vertices, indices):
    """Draw circular movement prediction"""
    # enemy_circular_center を Vector に変換
    center = Vector(obj.enemy_circular_center)  # 円の中心座標を Vector に変換
        
    # 半径を計算：オブジェクトの位置と中心との距離
    radius = (obj.location - center).length

    # 円を構成する頂点
    segments = 32
    start_idx = len(vertices["pos"])

    # 円を構成する頂点
    for i in range(segments):
        angle = (2 * math.pi / segments) * i
        x = center[0] + radius * math.cos(angle)
        y = center[1] + radius * math.sin(angle)
        z = center[2]
        vertices["pos"].append([x, y, z])

    # インデックスで線を形成
    for i in range(segments):
        indices.append((start_idx + i, start_idx + (i + 1) % segments))


