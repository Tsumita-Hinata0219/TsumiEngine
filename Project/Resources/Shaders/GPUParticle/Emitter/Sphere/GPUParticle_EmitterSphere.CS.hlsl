#include "../../GPUParticle.hlsli"


// パーティクルの最大インスタンス数
static const uint kParticleInstanceMax = 1024;
// パーティクルの要素
RWStructuredBuffer<ParticleCS> gParticles : register(u0);

// FreeList
RWStructuredBuffer<int> gFreeList : register(u1);
// FreeListIndex
RWStructuredBuffer<int> gFreeListIndex : register(u2);

// Emitter emission related
ConstantBuffer<EmitterConfig> gEmitterConfig : register(b0);
// Emitter Sphere
ConstantBuffer<EmitterSphere> gEmitterSphere : register(b1);
// Emitter Range
ConstantBuffer<EmitterRange> gEmitterRange : register(b2);
// Random seed value
ConstantBuffer<RandomSeed> gRandomSeed : register(b3);


[numthreads(1, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    // 射出許可が出たので射出
    if (gEmitterConfig.isEmitting != 0)
    {
        // Random generator
        RandomGenerator rng;
        rng.InitSeed(gRandomSeed.gameTime, (gRandomSeed.dynamicTime));
        // Set range Scale
        float3 scaleMin = float3(0.2f, 0.2f, 2.0f);
        float3 scaleMax = float3(0.6f, 0.6f, 0.6f);
        // Set translate range
        float3 translateMin = float3(-2.0f, -2.0f, -2.0f);
        float3 translateMax = float3(2.0f, 2.0f, 2.0f);
        // Set ColorRGB range
        float3 colorMin = float3(0.0f, 0.0f, 0.0f);
        float3 colorMax = float3(1.0f, 1.0f, 1.0f);
        
        // 射出するパーティクル数
        uint spawnCount = gEmitterConfig.spawnCount;
        
        // Number of particles
        for (uint countIndex = 0; countIndex < spawnCount; ++countIndex)
        {
            int freeListIndex;
            // FreeListのIndexを1つ前に設定し、現在のIndexを取得する
            InterlockedAdd(gFreeListIndex[0], -1, freeListIndex);
            
            // 最大数よりもparticleの数が少なければ射出
            if (0 <= freeListIndex && freeListIndex < kParticleInstanceMax)
            {
                int particleIndex = gFreeList[freeListIndex];
                // SRT
                gParticles[particleIndex].scale = rng.RandomRange3D(scaleMin, scaleMax);
                gParticles[particleIndex].rotate = float3(0.0f, 0.0f, 0.0f);
                gParticles[particleIndex].translate = rng.RandomRange3D(translateMin, translateMax);
                gParticles[particleIndex].matWorld = AffineMatrix(gParticles[particleIndex].scale, gParticles[particleIndex].rotate, gParticles[particleIndex].translate);
                
                // Color
                gParticles[particleIndex].color.rgb = rng.RandomRange3D(colorMin, colorMax);
                gParticles[particleIndex].color.a = 1.0f; // Alphaは不透明固定
                
                // 生存フラグ
                gParticles[particleIndex].isAlive = true;
                
                // 生存時間
                gParticles[particleIndex].lifeTime = 1 * 60;
            }
            else
            {
                // 発生させられなかったので、減らしてしまった分もとに戻す
                InterlockedAdd(gFreeListIndex[0], 1);
                // Emit中にParticleは消えないので、この後発生することはないためbrekaして終わらせる
                break;
            }
        }
    }
}
