#include "../Emitter.hlsli"
#include "../../GPUParticle/GPUParticle.hlsli"
#include "../../Math/Math.hlsli"
#include "../../Random/Random.hlsli"


// パーティクルの最大インスタンス数
static const uint kParticleInstanceMax = 1024;
// パーティクルの要素
RWStructuredBuffer<ParticleCS> gParticles : register(u0);

// FreeList
RWStructuredBuffer<int> gFreeList : register(u1);
// FreeListIndex
RWStructuredBuffer<int> gFreeListIndex : register(u2);

// Emitter Sphere
ConstantBuffer<EmitterSphere> gEmitSphere : register(b0);
// Emitter Range
ConstantBuffer<EmitterRange> gEmitRange : register(b1);
// Emitter emission related
ConstantBuffer<EmitterConfig> gEmitConfig : register(b2);
// Random seed value
ConstantBuffer<RandomSeed> gRandomSeed : register(b3);


[numthreads(1, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    // 射出許可が出たので射出
    if (gEmitConfig.isEmitting != 0)
    {
        // Random generator
        RandomGenerator rng;
        rng.InitSeed(gRandomSeed.gameTime, (gRandomSeed.dynamicTime + DTid.x * 0.5f));
        
        // Number of particles
        for (uint countIndex = 0; countIndex < gEmitConfig.spawnCount; ++countIndex)
        {
            int freeListIndex;
            // FreeListのIndexを1つ前に設定し、現在のIndexを取得する
            InterlockedAdd(gFreeListIndex[0], -1, freeListIndex);
            
            // 最大数よりもparticleの数が少なければ射出
            if (0 <= freeListIndex && freeListIndex < kParticleInstanceMax)
            {
                int particleIndex = gFreeList[freeListIndex];
                // SRT
                gParticles[particleIndex].scale = rng.RandomRange3D(gEmitRange.scaleMin.xyz, gEmitRange.scaleMax.xyz);
                gParticles[particleIndex].rotate = float3(0.0f, 0.0f, 0.0f);
                gParticles[particleIndex].translate = rng.RandomRange3D(gEmitRange.translateMin.xyz, gEmitRange.translateMax.xyz);
                gParticles[particleIndex].matWorld = AffineMatrix(gParticles[particleIndex].scale, gParticles[particleIndex].rotate, gParticles[particleIndex].translate);
                
                // Color
                gParticles[particleIndex].color.rgb = rng.RandomRange3D(gEmitRange.colorMin.xyz, gEmitRange.colorMax.xyz);
                gParticles[particleIndex].color.a = 1.0f; // Alphaは不透明固定
                
                // 生存フラグ
                gParticles[particleIndex].isAlive = true;
                
                // 生存時間
                gParticles[particleIndex].lifeTime = gEmitRange.baseLifeTime + rng.RandomRange1D(gEmitRange.lifeTimeMin, gEmitRange.lifeTimeMax);

                // Velocity
                gParticles[particleIndex].velocity = rng.RandomRange3D(gEmitRange.velocityMin.xyz, gEmitRange.velocityMax.xyz);

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
