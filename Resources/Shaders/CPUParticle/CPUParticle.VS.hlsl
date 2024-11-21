#include "CPUParticle.hlsli"


// �g�����X�t�H�[��
StructuredBuffer<TransformationMatrix> gTransformationMat : register(t0);
// �J����
ConstantBuffer<ViewProjectionMatrix> gViewProjectionMat : register(b0);


// Main
VertexShaderOutput main(VertexShaderInput input, uint instanceID : SV_InstanceID)
{
    VertexShaderOutput output;
    
    float4x4 cameraMat = mul(gViewProjectionMat.view, gViewProjectionMat.projection);
    float4x4 wvpMat = gTransformationMat[instanceID].World;
    
    // ���_�̈ʒu�����[���h�E�r���[�E�v���W�F�N�V�����s��ŕϊ�
    output.position = mul(input.position, wvpMat);
    
    // �e�N�X�`�����W�͂��̂܂ܓn��
    output.texCoord = input.texCoord;
    
    // �@���x�N�g�������[���h�s��̋t�]�u�s��ŕϊ����A���K������
    output.normal = normalize(mul(input.normal, (float3x3) wvpMat));
    
    // InstanceID�͂��̂܂ܓn��
    output.instanceID = instanceID;
    
    return output;
}

