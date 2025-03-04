#include "../GPUParticle.hlsli"


// パーティクル最大インスタンス数
static const uint kMaclParticles = 1024;

// パーティクルの要素
RWStructuredBuffer<ParticleCS> gParticles : register(u0);

// FreeList
RWStructuredBuffer<int> gFreeList : register(u1);
// FreeListIndex
RWStructuredBuffer<int> gFreeListIndex : register(u2);


[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    int particleIndex = DTid.x;
    
    if (particleIndex < kMaclParticles)
    {
        // 生存中の処理
        if (gParticles[particleIndex].isAlive == 0)
        {
            // ParticleのMatWorldの更新処理
            gParticles[particleIndex].matWorld = AffineMatrix(gParticles[particleIndex].scale, gParticles[particleIndex].rotate, gParticles[particleIndex].translate);
            
            
            
            
            
            
            
        }
        else
        {
            // スケールに0を入れて、VertexShader出力で棄却されるようにする
            gParticles[particleIndex].scale = float3(0.0f, 0.0f, 0.0f);
            uint freeListIndex;
            InterlockedAdd(gFreeListIndex[0], 1, freeListIndex);
            // 最新のFreeListIndexの場所に死んだPaticleのIndexを設定する
            if ((freeListIndex + 1) < kMaclParticles)
            {
                gFreeList[freeListIndex + 1] = particleIndex;
            }
            else
            {
                // ここに来るはずはない。きたら何かが間違っているが、安全策をうっておく
                InterlockedAdd(gFreeListIndex[0], -1, freeListIndex);
            }
        }
    }
}
