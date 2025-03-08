#include "../GPUParticle.hlsli"


// �p�[�e�B�N���ő�C���X�^���X��
static const uint kParticleInstanceMax = 1024;
// �p�[�e�B�N���̗v�f
RWStructuredBuffer<ParticleCS> gParticles : register(u0);
// �p�[�e�B�N���̋����v�f
RWStructuredBuffer<ParticleMotion> gPartMotion : register(u1);

// FreeList
RWStructuredBuffer<int> gFreeList : register(u2);
// FreeListIndex
RWStructuredBuffer<int> gFreeListIndex : register(u3);


[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    int particleIndex = DTid.x;
    
    // �p�[�e�B�N���̏�����
    if (particleIndex < kParticleInstanceMax)
    {
        // freeList�̏�����
        gFreeList[particleIndex] = particleIndex;
        
        // particle�\���̂̑S�v�f��0�Ŗ��߂�
        gParticles[particleIndex] = (ParticleCS) 0;
        gParticles[particleIndex].matWorld = Mat4x4Identity();
        
        // �����t���O�͐܂��Ă���
        gParticles[particleIndex].isAlive = false;
        
        // �������Ԃ�0�ŏ�����
        gParticles[particleIndex].lifeTime = 0;
        
        // Velocity��0�ŏ�����
        gPartMotion[particleIndex].velocity = float3(0.0f, 0.0f, 0.0f);
    }
    // �J�E���^�[������
    if (particleIndex == 0)
    {
        gFreeListIndex[0] = kParticleInstanceMax - 1;
    }
}
