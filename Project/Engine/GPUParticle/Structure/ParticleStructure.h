#pragma once

#include "Math/MyMath.h"


namespace GpuParticle {

// Particleを表す構造体
struct PropertyCS {
	Vector3 scale{};
	Vector3 rotate{};
	Vector3 translate{};
	Matrix4x4 matWorld{};
	Vector4 color{};
};

// Material
struct Material {
	Vector4 color;
	Matrix4x4 uvTransform;
};

// PreView
struct PreView {
	Matrix4x4 viewProjection;
	Matrix4x4 billboardMatrix;
};

// 射出に関する共通設定
struct EmitterConfig {
	uint32_t particleCount;  // 1回の射出で生成するパーティクル数
	float emitInterval;      // パーティクルを射出する間隔（秒）
	float intervalTime;      // 射出間隔調整用時間
	uint32_t enableEmit;     // 射出許可フラグ (0: 停止, 1: 許可)
};

// Emitter_Sphere
struct SphereEmitter {
	Vector3 translate{};     // 位置
	float radius;            // 射出半径
};

// 乱数のシード情報
struct RandomSeed {
	float gameTime; 
	float dynamicTime;
};

}