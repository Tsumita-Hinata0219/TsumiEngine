#include "../GPUParticle.hlsli"


// パーティクル最大インスタンス数
static const uint kMaclParticles = 1024;

// パーティクルの要素
RWStructuredBuffer<ParticleCS> gParticles : register(u0);

[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    int particleIndex = DTid.x;
    
    if (particleIndex < kMaclParticles)
    {
        // ParticleのMatWorldの更新処理
        gParticles[particleIndex].matWorld = AffineMatrix(
        gParticles[particleIndex].scale, gParticles[particleIndex].rotate, gParticles[particleIndex].translate);
    }
}
