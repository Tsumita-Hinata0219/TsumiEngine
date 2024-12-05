#pragma once


// オブジェクトの属性
enum class ObjAttribute {
    NONE,
    PLAYER,
    PLAYERBULLET,
    ENEMY,
    ENEMYBULLET,
    TERRAIN,
    OTHER,
};


enum class ObjCategory {
    NONE,
    PLAYER,
    ENEMY,
    TERRAIN,
    OTHER,
};

enum class ObjType {
    NONE,
    BODY,       // プレイヤー本体
    BULLET,     // プレイヤーの弾
    SOLID,      // 固い地形（障害物）
    PASSABLE,   // 通れる地形
    OTHER       // その他
};
