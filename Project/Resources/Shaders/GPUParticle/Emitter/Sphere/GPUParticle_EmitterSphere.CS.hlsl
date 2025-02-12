#include "../../GPUParticle.hlsli"


// パーティクル最大インスタンス数
static const uint kMaclParticles = 1024;

// パーティクルの要素
RWStructuredBuffer<ParticleCS> gParticles : register(u0);

// Emitterの射出関連
ConstantBuffer<EmitterConfig> gEmitterConfig : register(b0);


[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    // 射出許可が出たので射出
    if (gEmitterConfig.enableEmit != 0)
    {
        for (uint32_t countIndex = 0; countIndex < gEmitterConfig.particleCount; ++countIndex)
        {
            // カウント分Particleを射出する
            gParticles[countIndex].scale = float32_t3(0.3f, 0.3f, 0.3f);
            gParticles[countIndex].translate = float32_t3(0.0f, 0.0f, 0.0f);
            gParticles[countIndex].color = float32_t4(1.0f, 0.0f, 0.0f, 1.0f);
        }

    }
}
