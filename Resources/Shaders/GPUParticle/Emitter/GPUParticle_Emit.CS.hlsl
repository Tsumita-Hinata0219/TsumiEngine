#include "../GPUParticle.hlsli"

// Emitterの要素
ConstantBuffer<SphereEmitter> gEmitter : register(b0);

// Particleの要素
RWStructuredBuffer<ParticleCS> gParticles : register(u0);


// 今回スレッド数は1。複数のEmitterを扱い、同時に処理したい場合は適宜すれっと数を増やすといい
[numthreads(1, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    // 射出許可が出たので射出
    if (gEmitter.emit != 0)
    {
        for (uint countIndex = 0; countIndex < gEmitter.count; ++countIndex)
        {
            // カウント分Particleを射出する
            gParticles[countIndex].scale = float3(0.3f, 0.3f, 0.3f);
            gParticles[countIndex].translate = float3(2.0f, 0.0f, 0.0f);
            gParticles[countIndex].color = float4(1.0f, 0.0f, 0.0f, 1.0f);
            gParticles[countIndex].matWorld = AffineMatrix(gParticles[countIndex].scale, float3(0.0f, 0.0f, 0.0f), gParticles[countIndex].translate);

        }

    }
}