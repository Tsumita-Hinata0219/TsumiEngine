#include "GPUParticle.hlsli"


// Particle�̗v�f
RWStructuredBuffer<ParticleCS> gParticles : register(u0);
// Particle�̍ő吔
static int kMaxParticles = 1024;

[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    int particleIndex = DTid.x;
    
    if (particleIndex < kMaxParticles)
    {
        // particle�\���̂̑S�v�f��0�Ŗ��߂�Ƃ���������
        gParticles[particleIndex] = (ParticleCS)0;
    }
}
