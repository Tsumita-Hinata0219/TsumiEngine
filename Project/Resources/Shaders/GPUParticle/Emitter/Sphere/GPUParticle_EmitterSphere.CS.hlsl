#include "../../GPUParticle.hlsli"


// パーティクル最大インスタンス数
static const uint kMaclParticles = 1024;

// パーティクルの要素
RWStructuredBuffer<ParticleCS> gParticles : register(u0);

// Emitterの射出関連
ConstantBuffer<EmitterConfig> gEmitterConfig : register(b0);

// RandomのSeedの値
ConstantBuffer<RandomSeed> gRandomSeed : register(b1);


[numthreads(1, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    // 射出許可が出たので射出
    //if (gEmitterConfig.enableEmit != 0)
    {
        // 乱数生成器
        RandomGenerator rng;
        // シードの設定
        rng.seed3D = float3(1.0, 2.0, 3.0);
        rng.seed2D = float2(4.0, 5.0);
        rng.seed4D = float4(6.0, 7.0, 8.0, 9.0);
        // 範囲の設定
        // スケール
        float3 scaleMin = float3(0.2f, 0.2f, 1.0f);
        float3 scaleMax = float3(1.0f, 1.0f, 1.0f);
        // 座標
        float3 translateMin = float3(-3.0f, -3.0f, -3.0f);
        float3 translateMax = float3(3.0f, 3.0f, 3.0f);
        // カラー RGB
        float3 colorMin = float3(0.0f, 0.0f, 0.0f);
        float3 colorMax = float3(1.0f, 1.0f, 1.0f);
        
        for (uint countIndex = 0; countIndex < 10; ++countIndex)
        {
            // カウント分Particleを射出する
            gParticles[countIndex].scale = rng.RandomRange3D(scaleMin, scaleMax);
            gParticles[countIndex].translate = rng.RandomRange3D(translateMin, translateMax);
            gParticles[countIndex].color.rgb = rng.RandomRange3D(colorMin, colorMax);
            gParticles[countIndex].color.a = 1.0f;
        }
    }
}
