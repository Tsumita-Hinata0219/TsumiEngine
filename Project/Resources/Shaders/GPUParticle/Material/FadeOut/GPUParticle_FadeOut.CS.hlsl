#include "../../GPUParticle.hlsli"
#include "../../../Math/Math.hlsli"
#include "../../../Random/Random.hlsli"


// パーティクル最大インスタンス数
static const uint kParticleInstanceMax = 1024;

// パーティクルの要素
RWStructuredBuffer<ParticleCS> gParticles : register(u0);
// パーティクルの生存時間
RWStructuredBuffer<ParticleLifeTime> gLifeTime : register(u1);

// パーティクルのFadeOut数値
ConstantBuffer<ParticleFadeOut> gFadeOut : register(b0);


[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    int particleIndex = DTid.x;
    
    if (particleIndex < kParticleInstanceMax)
    {
        // 生存中の処理
        if (gParticles[particleIndex].isAlive != 0)
        {
            float ratio = gLifeTime[particleIndex].ratio;
            float fadeStart = gFadeOut.fadeStart;
            float fadeEnd = gFadeOut.fadeEnd;
            float fadePower = gFadeOut.fadePower;

            // 初期値：不透明
            float fadeAlpha = 1.0f;

            // ratio が fadeStart を超えたらフェード開始
            if (ratio >= fadeStart)
            {
                float fadeRange = fadeEnd - fadeStart;
                float localT = saturate((ratio - fadeStart) / fadeRange);

                // フェード値（e.g. powでカーブ調整）
                fadeAlpha = pow(1.0f - localT, fadePower);
            }

            gParticles[particleIndex].color.a = fadeAlpha;
        }
    }
}
