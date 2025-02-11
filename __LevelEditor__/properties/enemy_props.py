import bpy
import mathutils
from bpy.props import StringProperty, EnumProperty, BoolProperty, IntProperty, FloatProperty, FloatVectorProperty


# ──────────── エネミープロパティ
class Enemy_Props(bpy.types.PropertyGroup):
    obj = bpy.types.Object
    # shot direction
    obj.enemy_shot_direction = EnumProperty(
        name="Shot Direction",
        items=[
            ('NONE', "none", ""),
            ('FORWARD', "forward", ""),
            ('TRIPLE_FORWARD', "triple forward", ""),
            ('CROSS', "cross", ""),
            ('OMNI_FOUR', "omni four", ""),
            ('OMNI_FIVE', "omni five", ""),
            ('OMNI_EIGHT', "omni eight", ""),
            ('RANDOM', "random", ""),
        ],
        default='NONE'
    )
    # bullet behavior
    obj.enemy_bullet_behavior = EnumProperty(
        name="Bullet Behavior",
        items=[
            ('NONE', "none", ""),
            ('COMMON', "common", ""),
            ('RESISTANT', "resistant", ""),
            ('RANDOM', "random", ""),
        ],
        default='NONE'
    )
    
    # shot interval
    obj.enemy_shoot_interval = IntProperty(
        name="Shoot Interval",
        default=10,
        min=1,  # Minimum value
        max=10000,  # Maximum valueS
        description="Interval between shots"
    )

    # move behavior
    obj.enemy_move_behavior = EnumProperty(
        name="Move Behavior",
        items=[
            ('NONE', "none", ""),
            ('STATIC', "static", ""),
            ('FOLLOW', "follow", ""),
            ('HORIZONTAL', "horizontal", ""),
            ('CIRCULAR', "circular", ""),
        ],
        default='NONE'
    )

    # move speed
    obj.enemy_move_speed = FloatProperty(
        name="Circular Speed",
        description="Speed of circular movement",
        default=5.0,
        min=-1000.0,
        max=1000.0
    )

    # horizontal
    obj.enemy_horizontal_start = FloatVectorProperty(    
        name="Horizontal Start",
        description="Start point of horizontal movement",    
        size=3,  # 位置は3D座標なのでsize=3    
        default=(0.0, 0.0, 0.0),  # 初期値,
    )
    obj.enemy_horizontal_end  = FloatVectorProperty(    
        name="Horizontal End",
        description="Start point of horizontal movement",    
        size=3,  # 位置は3D座標なのでsize=3    
        default=(0.0, 0.0, 0.0),  # 初期値,
    )
    
    # circular 
    obj.enemy_circular_center = bpy.props.FloatVectorProperty(    
        name="Circular Center",
        description="Center position for circular movement",
        size=3,  # 位置は3D座標なのでsize=3
        default=(0.0, 0.0, 0.0)  # 初期値
    )

    # Tilt Body Flag
    obj.enemy_tilt_body = BoolProperty(
        name="Tilt Body",
        description="Enable body tilting",
        default=False
    )
    

# ──────────── エネミープロパティを描画
def draw_enemy_properties(layout, obj):
    # Shot Direction
    row = layout.row()
    row.label(text="Shot Direction :")
    row.prop(obj, "enemy_shot_direction", text="")

    # Bullet Behavior
    row = layout.row()
    row.label(text="Bullet Behavior :")
    row.prop(obj, "enemy_bullet_behavior", text="")

    # Shoot Interval
    layout.prop(obj, "enemy_shoot_interval", text="Shoot Interval")
    
    # 区切り線
    layout.separator()

    # Move Behavior
    row = layout.row()
    row.label(text="Move Behavior :")
    row.prop(obj, "enemy_move_behavior", text="")
    # Tilt Body
    layout.prop(obj, "enemy_tilt_body", text="Tilt Body")
    if obj.enemy_move_behavior == 'FOLLOW':
        # move speed
        layout.prop(obj, "enemy_move_speed", text="Move Speed")
    elif obj.enemy_move_behavior == 'HORIZONTAL':
        # move speed
        layout.prop(obj, "enemy_move_speed", text="Move Speed")
        # horizontal
        layout.prop(obj, "enemy_horizontal_start", text="start")
        layout.prop(obj, "enemy_horizontal_end", text="end")
    elif obj.enemy_move_behavior == 'CIRCULAR':
        # move speed
        layout.prop(obj, "enemy_move_speed", text="Move Speed")
        # circular
        layout.prop(obj, "enemy_circular_center", text="Center")

    # 区切り線
    layout.separator()


# ──────────── Json出力するエネミー情報を取得
def get_enemy_data(category_data, obj):
    """カテゴリのデータを追加"""
    shot_direction = obj.enemy_shot_direction
    bullet_behavior = obj.enemy_bullet_behavior
    shoot_interval = obj.enemy_shoot_interval
    move_behavior = obj.enemy_move_behavior
    tilt_body = obj.enemy_tilt_body
    move_speed = obj.enemy_move_speed
    horizontal_start = list(obj.enemy_horizontal_start)
    horizontal_end = list(obj.enemy_horizontal_end)
    circular_center = list(obj.enemy_circular_center)

    # Shot Direction
    category_data["shot_direction"] = shot_direction

    # Bullet Behavior
    category_data["bullet_behavior"] = bullet_behavior

    # Shoot Interval
    category_data["shoot_interval"] = shoot_interval

    # Move Behavior
    category_data["move_behavior"] = move_behavior
    
    # Move Props
    # Tilt Body
    category_data["tilt_body"] = tilt_body
    if move_behavior == 'FOLLOW':
        # move speed
        category_data["move_speed"] = move_speed
    elif move_behavior == 'HORIZONTAL':
        # move speed
        category_data["move_speed"] = move_speed
        # horizontal
        category_data["horizontal_start"] = [horizontal_start[0] + obj.location.x,
                                            horizontal_start[1] + obj.location.y,
                                            horizontal_start[2] + obj.location.z]
        category_data["horizontal_end"] = [horizontal_end[0] + obj.location.x,
                                            horizontal_end[1] + obj.location.y,
                                            horizontal_end[2] + obj.location.z]
    elif move_behavior == 'CIRCULAR':
        # move speed
        category_data["move_speed"] = move_speed
        # circular
        category_data["circular_center"] = circular_center
        # Calculate radius
        radius = ((circular_center[0] - obj.location.x) ** 2 +
                  (circular_center[1] - obj.location.y) ** 2 +
                  (circular_center[2] - obj.location.z) ** 2) ** 0.5
        category_data["circular_radius"] = radius
 

def get_relative_position(obj, world_position):
    """親オブジェクトの位置を基に相対座標を計算"""
    if obj.parent:
        # 親がある場合、親の位置を基にしたローカル座標を返す
        return obj.parent.matrix_world.inverted() @ world_position
    else:
        # 親がない場合、そのままの座標を返す
        return world_position