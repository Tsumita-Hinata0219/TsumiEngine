#include "../../GPUParticle.hlsli"
#include "../../../Math/Math.hlsli"
#include "../../../Random/Random.hlsli"


// パーティクル最大インスタンス数
static const uint kParticleInstanceMax = 1024;
// パーティクルの要素
RWStructuredBuffer<ParticleCS> gParticles : register(u0);


[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    int particleIndex = DTid.x;
    
    if (particleIndex < kParticleInstanceMax)
    {
        // 生存中の処理
        if (gParticles[particleIndex].isAlive != 0)
        {
            
            
        }
        else
        {
            
        }
    }
}
