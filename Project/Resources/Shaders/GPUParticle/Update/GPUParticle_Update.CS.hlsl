#include "../GPUParticle.hlsli"


// �p�[�e�B�N���ő�C���X�^���X��
static const uint kMaclParticles = 1024;

// �p�[�e�B�N���̗v�f
RWStructuredBuffer<ParticleCS> gParticles : register(u0);

[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    int particleIndex = DTid.x;
    
    if (particleIndex < kMaclParticles)
    {
        // Particle��MatWorld�̍X�V����
        gParticles[particleIndex].matWorld = AffineMatrix(
        gParticles[particleIndex].scale, gParticles[particleIndex].rotate, gParticles[particleIndex].translate);
    }
}
