import bpy

def register_classes(classes):
    """
    クラスリストの登録処理
    """
    for cls in classes:
        # クラスが登録済みか確認し、登録解除
        if cls.is_registered:
            bpy.utils.unregister_class(cls)
        bpy.utils.register_class(cls)

def unregister_classes(classes):
    """
    クラスリストの登録解除処理
    """
    for cls in reversed(classes):  # 逆順で解除
        if cls.is_registered:
            bpy.utils.unregister_class(cls)
