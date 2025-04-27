#include "../GPUParticle.hlsli"
#include "../../Math/Math.hlsli"
#include "../../Random/Random.hlsli"


// �p�[�e�B�N���ő�C���X�^���X��
static const uint kParticleInstanceMax = 1024;
// �p�[�e�B�N���̗v�f
RWStructuredBuffer<ParticleCS> gParticles : register(u0); 
// �p�[�e�B�N���̐�������
RWStructuredBuffer<ParticleLifeTime> gLifeTime : register(u1);

// FreeList
RWStructuredBuffer<int> gFreeList : register(u2);
// FreeListIndex
RWStructuredBuffer<int> gFreeListIndex : register(u3);


[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    int particleIndex = DTid.x;
    
    if (particleIndex < kParticleInstanceMax)
    {
        // �������̏���
        if (gParticles[particleIndex].isAlive != 0)
        {
            // �������Ԃ�0�ȉ�
            if (gLifeTime[particleIndex].current <= 0.0f)
            {
                // �����t���O��܂�
                gParticles[particleIndex].isAlive = false;
            }
            
            // velocity�����Z
            gParticles[particleIndex].translate += gParticles[particleIndex].velocity;
            
            // Particle��MatWorld�̍X�V����
            gParticles[particleIndex].matWorld = AffineMatrix(gParticles[particleIndex].scale, gParticles[particleIndex].rotate, gParticles[particleIndex].translate);
        }
        else
        {
            // �X�P�[����0�����āAVertexShader�o�͂Ŋ��p�����悤�ɂ���
            gParticles[particleIndex].scale = float3(0.0f, 0.0f, 0.0f);
            uint freeListIndex;
            InterlockedAdd(gFreeListIndex[0], 1, freeListIndex);
            
            // �ŐV��FreeListIndex�̏ꏊ�Ɏ���Paticle��Index��ݒ肷��
            if ((freeListIndex + 1) < kParticleInstanceMax)
            {
                gFreeList[freeListIndex + 1] = particleIndex;
            }
            else
            {
                // �C���f�b�N�X���͈͊O�ɂȂ�̂�h��
                InterlockedAdd(gFreeListIndex[0], -1, freeListIndex);
            }
        }
    }
}
