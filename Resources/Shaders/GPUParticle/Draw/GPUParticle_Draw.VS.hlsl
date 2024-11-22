#include "../GPUParticle.hlsli"


// Particle�̗v�f
StructuredBuffer<ParticleCS> gParticles : register(t0);
// PreView
ConstantBuffer<PreView> gPreView : register(b0);

// Main
VertexShaderOutput main(VertexShaderInput input, uint instanceID : SV_InstanceID)
{
    VertexShaderOutput output;
    
    ParticleCS particle = gParticles[instanceID];
    float4x4 worldMatrix = gPreView.billboardMatrix; // worldMatrix�����
    worldMatrix[0] += particle.scale.x;
    worldMatrix[1] += particle.scale.y;
    worldMatrix[2] += particle.scale.z;
    worldMatrix[3].xyz += particle.translate;
    
    // ���_�̈ʒu�����[���h�E�r���[�E�v���W�F�N�V�����s��ŕϊ�
    output.position = mul(input.position, mul(worldMatrix, gPreView.viewProjection));
    
    // �e�N�X�`�����W�͂��̂܂ܓn��
    output.texcoord = input.texcoord;
    
    // InstanceID�͂��̂܂ܓn��
    output.instanceID = instanceID;
    
    return output;
}
