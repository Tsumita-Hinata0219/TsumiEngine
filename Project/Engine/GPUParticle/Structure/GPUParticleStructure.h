#pragma once

#include "Math/MyMath.h"

// GPUParticleの要素構造体
struct GPUParticleCS {
    Vector3 scale{};
    Vector3 rotate{};
    Vector3 translate{};
    Matrix4x4 matWorld{};
    Vector4 color{};
};

// GPUParticleMaterial
struct GPUParticleMaterial {
    Vector4 color;
    Matrix4x4 uvTransform;
};

// PreView
struct GPUParticlePreView {
    Matrix4x4 viewProjection;
    Matrix4x4 billboardMatrix;
};