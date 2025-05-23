#include "../../GPUParticle.hlsli"
#include "../../../Math/Math.hlsli"
#include "../../../Random/Random.hlsli"


// �p�[�e�B�N���ő�C���X�^���X��
static const uint kParticleInstanceMax = 1024;

// �p�[�e�B�N���̗v�f
RWStructuredBuffer<ParticleCS> gParticles : register(u0);
// �p�[�e�B�N���̐�������
RWStructuredBuffer<ParticleLifeTime> gLifeTime : register(u1);

// �p�[�e�B�N����FadeOut���l
ConstantBuffer<ParticleFadeOut> gFadeOut : register(b0);


[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    uint index = DTid.x;

    //if (particleIndex >= kParticleInstanceMax)
    //    return;
    //if (gParticles[particleIndex].isAlive == 0)
    //    return;

    //// ratio�i�i�s�x�j��1.0�ɋ߂Â��ɂ�ă���0�ɋ߂Â�
    //float ratio = gLifeTime[particleIndex].ratio;

    //// �P���Ȑ��`�t�F�[�h
    //gParticles[particleIndex].color.a = 1.0f - ratio;
    
    float ratio = gLifeTime[index].ratio;
    // ratio��ԁAalpha��΂ɏo�� �� ��ʂŊm�F���₷��
    gParticles[index].color.rgb = float3(ratio, gParticles[index].color.a, 0.0f);
    gParticles[index].color.a = 1.0f - ratio;

}
