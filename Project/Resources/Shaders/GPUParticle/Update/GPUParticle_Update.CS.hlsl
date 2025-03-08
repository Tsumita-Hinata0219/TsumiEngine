#include "../GPUParticle.hlsli"


// パーティクル最大インスタンス数
static const uint kParticleInstanceMax = 1024;
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
    
    if (particleIndex < kParticleInstanceMax)
    {
        // 生存中の処理
        if (gParticles[particleIndex].isAlive != 0)
        {
            // 生存時間の減算処理
            gParticles[particleIndex].lifeTime -= 1.0f;
            // 生存時間が0以下
            if (gParticles[particleIndex].lifeTime <= 0.0f)
            {
                // 生存フラグを折る
                gParticles[particleIndex].isAlive = false;
                // 生存時間は0を入れておく
                gParticles[particleIndex].lifeTime = 0.0f;
            }
            
            // velocityを加算
            gParticles[particleIndex].translate += gParticles[particleIndex].velocity;
            
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
            if ((freeListIndex + 1) < kParticleInstanceMax)
            {
                gFreeList[freeListIndex + 1] = particleIndex;
            }
            else
            {
                // インデックスが範囲外になるのを防ぐ
                InterlockedAdd(gFreeListIndex[0], -1, freeListIndex);
            }
        }
    }
}
