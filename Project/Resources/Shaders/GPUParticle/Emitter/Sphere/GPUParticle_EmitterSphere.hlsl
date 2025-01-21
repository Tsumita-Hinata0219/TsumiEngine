#include "../../GPUParticle.hlsli"


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
        // particle�\���̂̑S�v�f��0�Ŗ��߂�
        gParticles[particleIndex] = (ParticleCS) 0;
        gParticles[particleIndex].scale = float3(0.5f, 0.5f, 0.5f);
        gParticles[particleIndex].color = float4(1.0f, 1.0f, 1.0f, 1.0f);
        gParticles[particleIndex].matWorld = Mat4x4Identity();

    }
}
