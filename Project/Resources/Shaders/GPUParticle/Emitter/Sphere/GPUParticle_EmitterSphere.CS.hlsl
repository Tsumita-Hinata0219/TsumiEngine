#include "../../GPUParticle.hlsli"


// �p�[�e�B�N���ő�C���X�^���X��
static const uint kMaclParticles = 1024;

// �p�[�e�B�N���̗v�f
RWStructuredBuffer<ParticleCS> gParticles : register(u0);

// Emitter�̎ˏo�֘A
ConstantBuffer<EmitterConfig> gEmitterConfig : register(b0);


[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    // �ˏo�����o���̂Ŏˏo
    if (gEmitterConfig.enableEmit != 0)
    {
        for (uint32_t countIndex = 0; countIndex < gEmitterConfig.particleCount; ++countIndex)
        {
            // �J�E���g��Particle���ˏo����
            gParticles[countIndex].scale = float32_t3(0.3f, 0.3f, 0.3f);
            gParticles[countIndex].translate = float32_t3(0.0f, 0.0f, 0.0f);
            gParticles[countIndex].color = float32_t4(1.0f, 0.0f, 0.0f, 1.0f);
        }

    }
}
