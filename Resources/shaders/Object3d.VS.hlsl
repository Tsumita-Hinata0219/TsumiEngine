#include "Object3d.hlsli"
#include "MathFunc.hlsli"

struct TransformationMatrix
{
    float4x4 World;
    float4x4 WVP;
    float4x4 WorldInverseTranspose;
};
ConstantBuffer<TransformationMatrix> gTransformationMat : register(b0);


struct VertexShaderInput
{
    float4 position : POSITION0;
    float2 texCoord : TEXCOORD0;
    float3 normal : NORMAL0;
};


VertexShaderOutput main(VertexShaderInput input)
{    
    //VertexShaderOutput output;
    //float4x4 resultMat;

    //float4x4 cameraMat = mul(gTransformationViewMatrix.view, gTransformationViewMatrix.viewProjection);
    //resultMat = mul(gTransformationMatrix.World, cameraMat);

    //output.position = mul(input.position, resultMat);
    //output.texcoord = input.texcoord;
    //output.normal = normalize(mul(input.normal, (float3x3) gTransformationMatrix.World));
    //output.worldPosition = mul(input.position, gTransformationMatrix.World).xyz;
    //output.cameraPosition = gTransformationViewMatrix.cameraPosition;
    
    //return output;
    
    
    VertexShaderOutput output;
    
     // ���_�̈ʒu�����[���h�E�r���[�E�v���W�F�N�V�����s��ŕϊ�
    output.position = mul(input.position, gTransformationMat.WVP);
    
    // �e�N�X�`�����W�͂��̂܂ܓn��
    output.texCoord = input.texCoord;
    
    // �@���x�N�g�������[���h�s��̋t�]�u�s��ŕϊ����A���K������
    output.normal = normalize(mul(input.normal, (float3x3) gTransformationMat.WorldInverseTranspose));
    
    return output;
}