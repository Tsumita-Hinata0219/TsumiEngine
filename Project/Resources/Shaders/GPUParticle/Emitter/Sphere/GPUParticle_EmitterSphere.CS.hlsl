#include "../../GPUParticle.hlsli"


// パーティクル最大インスタンス数
static const uint kParticleInstanceMax = 1024;

// パーティクルの要素
RWStructuredBuffer<ParticleCS> gParticles : register(u0);

// FreeList
RWStructuredBuffer<int> gFreeList : register(u1);
// FreeListのIndex
RWStructuredBuffer<int> gFreeListIndex : register(u2);


// EmitterSphereの設定
ConstantBuffer<EmitterSphere> gEmitterSphere : register(b0);

// Emitterの射出関連
ConstantBuffer<EmitterConfig> gEmitterConfig : register(b1);

// RandomのSeedの値
ConstantBuffer<RandomSeed> gRandomSeed : register(b2);


[numthreads(1, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    // 射出許可が出たので射出
    if (gEmitterConfig.isEmitting != 0)
    {
        // 乱数生成器
        RandomGenerator rng;
        rng.InitSeed(gRandomSeed.gameTime, (gRandomSeed.dynamicTime));
        // 範囲の設定
        // スケール
        float3 scaleMin = float3(0.2f, 0.2f, 1.0f);
        float3 scaleMax = float3(0.6f, 0.6f, 0.6f);
        // 座標
        float3 translateMin = float3(-3.0f, -3.0f, -3.0f);
        float3 translateMax = float3(3.0f, 3.0f, 3.0f);
        // カラー RGB
        float3 colorMin = float3(0.0f, 0.0f, 0.0f);
        float3 colorMax = float3(1.0f, 1.0f, 1.0f);
        
        // 現在の生存しているパーティクル数
        uint spawnCount = gEmitterConfig.spawnCount;
        
        //個数
        for (uint countIndex = 0; countIndex < spawnCount; ++countIndex)
        {
            int freeListIndex;
            InterlockedAdd(gFreeListIndex[0], -1, freeListIndex);
            
            // 最大数よりもparticleの数が少なければ射出可能
            if (0 <= freeListIndex && freeListIndex < kParticleInstanceMax)
            {
                int particleIndex = gFreeList[freeListIndex];
                // カウント分Particleを射出する
                gParticles[particleIndex].scale = rng.RandomRange3D(scaleMin, scaleMax);
                gParticles[particleIndex].translate = rng.RandomRange3D(translateMin, translateMax);
                gParticles[particleIndex].color.rgb = rng.RandomRange3D(colorMin, colorMax);
                gParticles[particleIndex].color.a = 1.0f;
                
                // 生存フラグを立てる
                gParticles[particleIndex].isAlive = true;
                
            }
        }
    }
}
