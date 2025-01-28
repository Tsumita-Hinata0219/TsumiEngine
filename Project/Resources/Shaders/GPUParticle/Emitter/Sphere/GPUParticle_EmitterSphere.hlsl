#include "../../GPUParticle.hlsli"


// �p�[�e�B�N���ő�C���X�^���X��
static const uint kMaclParticles = 1024;

// �p�[�e�B�N���̗v�f
StructuredBuffer<EmitterSphere> gEmitterSphere : register(t0);


[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    int particleIndex = DTid.x;
    
    if (particleIndex < kMaclParticles)
    {
        // particle�\���̂̑S�v�f��0�Ŗ��߂�
        gEmitterSphere[particleIndex].count = 10;
        gEmitterSphere[particleIndex].frequency = 0.5f;
        gEmitterSphere[particleIndex].frequencyTime = 0.0f;
        gEmitterSphere[particleIndex].translate = float3(0.0f, 0.0f, 0.0f);
        gEmitterSphere[particleIndex].radius = 1.0f;
        gEmitterSphere[particleIndex].count = 1;
    }
}
