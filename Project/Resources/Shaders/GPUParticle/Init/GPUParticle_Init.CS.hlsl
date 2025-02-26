#include "../GPUParticle.hlsli"


// パーティクル最大インスタンス数
static const uint kMaclParticles = 1024;

// パーティクルの要素
RWStructuredBuffer<ParticleCS> gParticles : register(u0);

// カウンター
RWStructuredBuffer<uint> gFreeCounter : register(u1);

[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    int particleIndex = DTid.x;
    
    // カウンター初期化
    if (particleIndex == 0)
    {
        gFreeCounter[0] = 0;
    }
    
    // パーティクルの初期化
    if (particleIndex < kMaclParticles)
    {
        // particle構造体の全要素を0で埋める
        gParticles[particleIndex] = (ParticleCS) 0;
        gParticles[particleIndex].scale = float3(0.5f, 0.5f, 0.5f);
        gParticles[particleIndex].color = float4(1.0f, 1.0f, 1.0f, 1.0f);
        gParticles[particleIndex].matWorld = Mat4x4Identity();
    }
}
