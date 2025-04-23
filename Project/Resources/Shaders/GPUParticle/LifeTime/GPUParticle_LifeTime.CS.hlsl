#include "../GPUParticle.hlsli"
#include "../../Math/Math.hlsli"


// パーティクル最大インスタンス数
static const uint kParticleInstanceMax = 1024;
// パーティクルの要素
RWStructuredBuffer<ParticleCS> gParticles : register(u0);
// パーティクルの生存時間
RWStructuredBuffer<ParticleLifeTime> gLifeTime : register(u1);


[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    int particleIndex = DTid.x;
    
    if (particleIndex < kParticleInstanceMax)
    {
        if (gParticles[particleIndex].isAlive != 0)
        {
            // 生存時間の計算
            gLifeTime[particleIndex].current = max(gLifeTime[particleIndex].current - 1.0f, 0.0f);
            
            // 進行具合の計算
            gLifeTime[particleIndex].ratio = saturate(1.0f - gLifeTime[particleIndex].current / gLifeTime[particleIndex].end);

            // タイマー終了
            if (gLifeTime[particleIndex].current <= 0.0f)
            {
                gParticles[particleIndex].isAlive = false;
                gLifeTime[particleIndex].ratio = 1.0f;
            }
        }
    }
}
