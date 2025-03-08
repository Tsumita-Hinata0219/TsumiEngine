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
	uint32_t isAlive;
	uint32_t lifeTime;
};

// Particleの運動に関する構造体
struct ParticleMotion {
	Vector3 velocity; // 速度
	Vector3 acceleration; // 加速度
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

}