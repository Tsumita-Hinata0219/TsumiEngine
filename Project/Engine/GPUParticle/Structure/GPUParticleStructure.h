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

// Emitter_Sphere
struct EmitterSphere {
	Vector3 translate{}; // 位置
	float radius; // 射出半径
	uint32_t count; // 射出数
	float requency; // 射出間隔
	float frequencyTime; // 射出間隔調整用時間
	uint32_t emit; // 射出許可
};

}