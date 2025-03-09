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
        // �����x�ɂ�鑬�x�ω�
        gParticles[particleIndex].velocity += gField.acceleration;
        
        // �O�͓K�p
        gParticles[particleIndex].velocity += gField.force;

        // �p���x�K�p�i�������l�������e����^����j
        gParticles[particleIndex].velocity += cross(gField.angularVelocity, gParticles[particleIndex].velocity);

        // ���x�̌����idamping �� 0.0 �` 1.0 �͈̔́j
        gParticles[particleIndex].velocity *= gField.damping;

        // ��C��R�̉e���i���x�������قǒ�R���傫���Ȃ�j
        float speed = length(gParticles[particleIndex].velocity);
        if (speed > 0.0f)
        {
            float dragForce = 1.0f - gField.drag;
            gParticles[particleIndex].velocity *= max(dragForce, 0.0f);
        }
        
        gParticles[particleIndex].velocity = float3(0.0f, 0.0f, 0.0f);
    }
}