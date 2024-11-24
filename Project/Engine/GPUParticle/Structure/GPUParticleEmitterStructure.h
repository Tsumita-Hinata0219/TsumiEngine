#pragma once

#include "Math/MyMath.h"

// GPUParticleのエミッター
namespace GParticleEmitte {

	// Sphere型のEmitter
	struct SphereEmitter {
		Vector3 translate{}; // 座標
		float radius = 0.0f; // 射出半径
		uint32_t count = 0; // 射出数
		float frequency = 0.0f; // 射出間隔
		float frequencyTime = 0.0f; // 射出間隔調整用時間
		uint32_t emit = 0.0f; // 射出許可
	};

}