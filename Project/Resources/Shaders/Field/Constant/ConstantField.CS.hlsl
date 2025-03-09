#include "../Field.hlsli"
#include "../../GPUParticle/GPUParticle.hlsli"
#include "../../Math/Math.hlsli"
#include "../../Random/Random.hlsli"


// �p�[�e�B�N���ő�C���X�^���X��
static const uint kParticleInstanceMax = 1024;
// �p�[�e�B�N���̗v�f
RWStructuredBuffer<ParticleCS> gParticles : register(u0);

// ConstantField
ConstantBuffer<ConstantField> gField : register(b0);


[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    int particleIndex = DTid.x;
    
    // �t�B�[���h�g�p��
    if (gField.isUse)
    {
        ParticleCS particle = gParticles[particleIndex];

        // �����x�ɂ�鑬�x�ω�
        particle.velocity += gField.acceleration;
        
        // �O�͓K�p
        particle.velocity += gField.force;

        // �p���x�K�p�i�������l�������e����^����j
        particle.velocity += cross(gField.angularVelocity, particle.velocity);

        // ���x�̌����idamping �� 0.0 �` 1.0 �͈̔́j
        particle.velocity *= gField.damping;

        // ��C��R�̉e���i���x�������قǒ�R���傫���Ȃ�j
        float speed = length(particle.velocity);
        if (speed > 0.0)
        {
            float dragForce = 1.0 - gField.drag;
            particle.velocity *= max(dragForce, 0.0);
        }

        // �X�V�����p�[�e�B�N���f�[�^��ۑ�
        gParticles[particleIndex] = particle;
    }
}