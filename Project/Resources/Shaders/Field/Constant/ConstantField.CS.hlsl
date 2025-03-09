#include "../Field.hlsli"
#include "../../GPUParticle/GPUParticle.hlsli"
#include "../../Math/Math.hlsli"
#include "../../Random/Random.hlsli"


// パーティクル最大インスタンス数
static const uint kParticleInstanceMax = 1024;
// パーティクルの要素
RWStructuredBuffer<ParticleCS> gParticles : register(u0);

// ConstantField
ConstantBuffer<ConstantField> gField : register(b0);


[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    int particleIndex = DTid.x;
    
    // フィールド使用中
    if (gField.isUse)
    {
        ParticleCS particle = gParticles[particleIndex];

        // 加速度による速度変化
        particle.velocity += gField.acceleration;
        
        // 外力適用
        particle.velocity += gField.force;

        // 角速度適用（方向を考慮した影響を与える）
        particle.velocity += cross(gField.angularVelocity, particle.velocity);

        // 速度の減衰（damping は 0.0 ～ 1.0 の範囲）
        particle.velocity *= gField.damping;

        // 空気抵抗の影響（速度が速いほど抵抗が大きくなる）
        float speed = length(particle.velocity);
        if (speed > 0.0)
        {
            float dragForce = 1.0 - gField.drag;
            particle.velocity *= max(dragForce, 0.0);
        }

        // 更新したパーティクルデータを保存
        gParticles[particleIndex] = particle;
    }
}