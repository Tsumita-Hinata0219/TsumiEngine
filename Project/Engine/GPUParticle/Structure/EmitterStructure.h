#pragma once

#include "Math/MyMath.h"


namespace GpuEmitter {

// 射出に関する共通設定
struct EmitterConfig {
	uint32_t spawnCount;  // 1回の射出で生成するパーティクル数
	float spawnInterval = 0.0f;      // パーティクルを射出する間隔（秒）
	float elapsedTime = 0.0f;      // 射出間隔調整用時間
	uint32_t isEmitting;     // 射出許可フラグ (0: 停止, 1: 許可)
};

// Emitterの基底構造体
struct IEmitter {
	uint32_t aliveCount; // 生存しているパーティクル数
};

// Emitter_Sphere
struct SphereEmitter : IEmitter {
	Vector3 translate{};     // 位置
	float radius = 0.0f;     // 射出半径
};

// エミッターの範囲
struct EmitterRange
{
    // SRT
    Vector4 scaleMin;
    Vector4 scaleMax;
    Vector4 rotateMin;
    Vector4 rotateMax;
    Vector4 translateMin;
    Vector4 translateMax;
    // Color
    Vector4 colorMin;
    Vector4 colorMax;
    // Motion
    Vector4 velocityMin;
    Vector4 velocityMax;
    // Life
    float baseLifeTime = 0.0f;
    float lifeTimeMin = 0.0f;
    float lifeTimeMax = 0.0f;
};

// 乱数のシード情報
struct RandomSeed {
	float gameTime = 0.0f;
	float dynamicTime = 0.0f;
};

}