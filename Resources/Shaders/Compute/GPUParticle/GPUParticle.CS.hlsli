#include "GPUParticle.hlsli"


// Particleの要素
StructuredBuffer<ParticleCS> gParticles : register(t0);
// Particleの最大数
static int kMaxParticles = 1024;

[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    int particleIndex = DTid.x;
    
    if (particleIndex < kMaxParticles)
    {
        // particle構造体の全要素を0で埋めるという書き方
        gParticles[particleIndex] = (ParticleCS) 0;
    }
}
