#include "Object2d.hlsli"


struct TransformationMatrix
{
    float4x4 World;
    float4x4 WVP;
    float4x4 WorldInverseTranspose;
};
ConstantBuffer<TransformationMatrix> gTransformationMat : register(b0);


struct ViewProjectionMatrix
{
    float4x4 view;
    float4x4 projection;
    float4x4 orthoGraphic;
    float3 cameraPosition;
};
ConstantBuffer<ViewProjectionMatrix> gViewProjectionMat : register(b1);


struct VertexShaderInput
{
    float4 position : POSITION0;
    float2 texCoord : TEXCOORD0;
};


VertexShaderOutput main(VertexShaderInput input)
{
    VertexShaderOutput output;
    
    // ���_���W���s��Ƃ̌v�Z�ŋ��߂�
    float4x4 mat = mul(gTransformationMat.World, gViewProjectionMat.orthoGraphic);
    output.position = mul(input.position, mat);
    
    // �e�N�X�`�����W�͂��̂܂ܓn��
    output.texCoord = input.texCoord;    
    
    return output;
}
