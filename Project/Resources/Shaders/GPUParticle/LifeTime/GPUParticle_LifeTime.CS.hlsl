#include "../GPUParticle.hlsli"
#include "../../Math/Math.hlsli"


// �p�[�e�B�N���ő�C���X�^���X��
static const uint kParticleInstanceMax = 1024;
// �p�[�e�B�N���̗v�f
RWStructuredBuffer<ParticleCS> gParticles : register(u0);
// �p�[�e�B�N���̐�������
RWStructuredBuffer<ParticleLifeTime> gLifeTime : register(u1);


[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    int particleIndex = DTid.x;
    
    if (particleIndex < kParticleInstanceMax)
    {
        if (gParticles[particleIndex].isAlive != 0)
        {
            // �������Ԃ̌v�Z
            gLifeTime[particleIndex].current = max(gLifeTime[particleIndex].current - 1.0f, 0.0f);
            
            // �i�s��̌v�Z
            gLifeTime[particleIndex].ratio = saturate(1.0f - gLifeTime[particleIndex].current / gLifeTime[particleIndex].end);

            // �^�C�}�[�I��
            if (gLifeTime[particleIndex].current <= 0.0f)
            {
                gParticles[particleIndex].isAlive = false;
                gLifeTime[particleIndex].ratio = 1.0f;
            }
        }
    }
}
