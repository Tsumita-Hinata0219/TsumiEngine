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
    int particleIndex = DTid.x;
    
    if (particleIndex < kParticleInstanceMax)
    {
        // �������̏���
        if (gParticles[particleIndex].isAlive != 0)
        {
            float ratio = gLifeTime[particleIndex].ratio;
            float fadeStart = gFadeOut.fadeStart;
            float fadeEnd = gFadeOut.fadeEnd;
            float fadePower = gFadeOut.fadePower;

            // �����l�F�s����
            float fadeAlpha = 1.0f;

            // ratio �� fadeStart �𒴂�����t�F�[�h�J�n
            if (ratio >= fadeStart)
            {
                float fadeRange = fadeEnd - fadeStart;
                float localT = saturate((ratio - fadeStart) / fadeRange);

                // �t�F�[�h�l�ie.g. pow�ŃJ�[�u�����j
                fadeAlpha = pow(1.0f - localT, fadePower);
            }

            gParticles[particleIndex].color.a = fadeAlpha;
        }
    }
}
