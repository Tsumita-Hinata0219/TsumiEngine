#pragma once

#include "Math/MyMath.h"

// Particleを表す構造体
struct GPUParticleCS {
    Vector3 translate;
    Vector3 scale;
    float lifeTime;
    Vector3 velocity;
    float currentTime;
};

// Material
struct GPUParticleMaterial {
    Vector4 color;
    Matrix4x4 uvTransform;
};

// PreView
struct GPUParticlePreView {
    Matrix4x4 viewProjection;
    Matrix4x4 billboardMatrix;
};