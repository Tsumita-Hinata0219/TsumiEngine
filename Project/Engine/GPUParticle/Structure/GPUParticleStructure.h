#pragma once

#include "Math/MyMath.h"

// Particleを表す構造体
struct GPUParticle {
    Vector3 translate;
    Vector3 scale;
    float lifeTime;
    Vector3 velocity;
    float currentTime;
    Vector4 color;
};