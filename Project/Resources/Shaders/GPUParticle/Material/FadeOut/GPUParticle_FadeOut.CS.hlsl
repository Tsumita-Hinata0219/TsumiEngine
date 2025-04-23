#include "../../GPUParticle.hlsli"
#include "../../../Math/Math.hlsli"
#include "../../../Random/Random.hlsli"


// �p�[�e�B�N���ő�C���X�^���X��
static const uint kParticleInstanceMax = 1024;
// �p�[�e�B�N���̗v�f
RWStructuredBuffer<ParticleCS> gParticles : register(u0);


[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    int particleIndex = DTid.x;
    
    if (particleIndex < kParticleInstanceMax)
    {
        // �������̏���
        if (gParticles[particleIndex].isAlive != 0)
        {
            
            
        }
        else
        {
            
        }
    }
}
