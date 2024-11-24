#include "../GPUParticle.hlsli"


// Particleの要素
RWStructuredBuffer<ParticleCS> gParticles : register(u0);
// FreeCounter
RWStructuredBuffer<uint> gFreeCounter : register(u1);

// Emitterの要素
ConstantBuffer<SphereEmitter> gEmitter : register(b0);
// PreFrame
ConstantBuffer<PerFrame> gPerFrame : register(b1);



// 今回スレッド数は1。複数のEmitterを扱い、同時に処理したい場合は適宜すれっと数を増やすといい
[numthreads(1, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    // 疑似乱数生成器
    RandomGenerator generator;
    generator.seed = (DTid.x + gPerFrame.deltaTime) * gPerFrame.deltaTime;
    
    // 射出許可が出たので射出
    if (gEmitter.emit != 0)
    {
        for (uint countIndex = 0; countIndex < gEmitter.count; ++countIndex)
        {
            uint particleIndex;
            // gFreeCounter[0]に1を足し、足す前の値をparticleIndexに格納する
            InterlockedAdd(gFreeCounter[0], 1, particleIndex);
            
            // カウント分Particleを射出する
            gParticles[countIndex].scale = float3(1.0f, 1.0f, 1.0f);
            gParticles[countIndex].translate = generator.Generate3d();
            gParticles[countIndex].color = float4(1.0f, 0.0f, 0.0f, 1.0f);
            gParticles[countIndex].matWorld = AffineMatrix(gParticles[countIndex].scale, float3(0.0f, 0.0f, 0.0f), gParticles[countIndex].translate);

        }
    }
}