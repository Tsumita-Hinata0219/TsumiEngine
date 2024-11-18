#include "CPUParticle.hlsli"

struct TransformationMatrix
{
    float4x4 World;
    float4x4 WVP;
    float4x4 WorldInverseTranspose;
};
StructuredBuffer<TransformationMatrix> gTransformationMat : register(t0);


struct VertexShaderInput
{
    float4 position : POSITION0;
    float2 texCoord : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 worldPos : WORLDPOSITION0;
};


VertexShaderOutput main(VertexShaderInput input, int instanceID : SV_InstanceID)
{
    VertexShaderOutput output;
    
    // ���_�̈ʒu�����[���h�E�r���[�E�v���W�F�N�V�����s��ŕϊ�
    output.position = mul(input.position, gTransformationMat[instanceID].WVP);
    
    // �e�N�X�`�����W�͂��̂܂ܓn��
    output.texCoord = input.texCoord;
    
    // �@���x�N�g�������[���h�s��̋t�]�u�s��ŕϊ����A���K������
    output.normal = normalize(mul(input.normal, (float3x3) gTransformationMat[instanceID].WorldInverseTranspose));
    
    // ���[���h��Ԃł̈ʒu���v�Z���ďo�͂ɐݒ�
    output.worldPos = mul(input.position, gTransformationMat[instanceID].World).xyz;
    
    return output;
}
