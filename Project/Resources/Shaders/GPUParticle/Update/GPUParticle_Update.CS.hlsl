#include "../GPUParticle.hlsli"


// �p�[�e�B�N���ő�C���X�^���X��
static const uint kMaclParticles = 1024;

// �p�[�e�B�N���̗v�f
RWStructuredBuffer<ParticleCS> gParticles : register(u0);

// FreeList
RWStructuredBuffer<int> gFreeList : register(u1);
// FreeListIndex
RWStructuredBuffer<int> gFreeListIndex : register(u2);


[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    int particleIndex = DTid.x;
    
    if (particleIndex < kMaclParticles)
    {
        // �������̏���
        if (gParticles[particleIndex].isAlive == 0)
        {
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
            if ((freeListIndex + 1) < kMaclParticles)
            {
                gFreeList[freeListIndex + 1] = particleIndex;
            }
            else
            {
                // �����ɗ���͂��͂Ȃ��B�����牽�����Ԉ���Ă��邪�A���S��������Ă���
                InterlockedAdd(gFreeListIndex[0], -1, freeListIndex);
            }
        }
    }
}
