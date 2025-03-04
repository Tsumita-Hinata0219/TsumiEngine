#pragma once

#include "Math/MyMath.h"


namespace GpuEmitter {

// 射出に関する共通設定
struct EmitterConfig {
	uint32_t spawnCount;  // 1回の射出で生成するパーティクル数
	float spawnInterval;      // パーティクルを射出する間隔（秒）
	float elapsedTime;      // 射出間隔調整用時間
	uint32_t isEmitting;     // 射出許可フラグ (0: 停止, 1: 許可)
};

// Emitterの基底構造体
struct IEmitter {
	uint32_t aliveCount; // 生存しているパーティクル数
};

// Emitter_Sphere
struct SphereEmitter : IEmitter {
	Vector3 translate{};     // 位置
	float radius;            // 射出半径
};

// 乱数のシード情報
struct RandomSeed {
	float gameTime;
	float dynamicTime;
};

}