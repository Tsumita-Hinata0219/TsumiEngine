#include "../GPUParticle.hlsli"


// パーティクル最大インスタンス数
static const uint kParticleInstanceMax = 1024;
// パーティクルの要素
RWStructuredBuffer<ParticleCS> gParticles : register(u0);
// パーティクルの挙動要素
RWStructuredBuffer<ParticleMotion> gPartMotion : register(u1);

// FreeList
RWStructuredBuffer<int> gFreeList : register(u2);
// FreeListIndex
RWStructuredBuffer<int> gFreeListIndex : register(u3);


[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    int particleIndex = DTid.x;
    
    // パーティクルの初期化
    if (particleIndex < kParticleInstanceMax)
    {
        // freeListの初期化
        gFreeList[particleIndex] = particleIndex;
        
        // 全要素を0で埋める
        gParticles[particleIndex] = (ParticleCS) 0;
        gParticles[particleIndex].matWorld = Mat4x4Identity();
        
        // 全要素を0で埋める
        gPartMotion[particleIndex] = (ParticleMotion) 0;
    }
    // カウンター初期化
    if (particleIndex == 0)
    {
        gFreeListIndex[0] = kParticleInstanceMax - 1;
    }
}
