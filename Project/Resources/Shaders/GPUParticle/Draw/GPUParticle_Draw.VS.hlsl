#include "../GPUParticle.hlsli"


// Particle�̗v�f
RWStructuredBuffer<ParticleCS> gParticles : register(u0);

// �J����
ConstantBuffer<ViewProjectionMatrix> gViewProjectionMat : register(b0);


// Main
VertexShaderOutput main(VertexShaderInput input, uint instanceID : SV_InstanceID)
{
    VertexShaderOutput output;
    
    float32_t4x4 cameraMat = mul(gViewProjectionMat.view, gViewProjectionMat.projection);
  
    float4x4 wvpMat = mul(gParticles[instanceID].matWorld, cameraMat);
    
    // ���_�̈ʒu�����[���h�E�r���[�E�v���W�F�N�V�����s��ŕϊ�
    output.position = mul(input.position, wvpMat);
    
    // �e�N�X�`�����W�͂��̂܂ܓn��
    output.texCoord = input.texCoord;
    output.normal = input.normal;
    // InstanceID�͂��̂܂ܓn��
    output.instanceID = instanceID;
    
    return output;
}
