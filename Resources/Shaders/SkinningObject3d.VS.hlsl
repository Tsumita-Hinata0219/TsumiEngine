#include "SkinningObject3d.hlsli"

struct TransformationMatrix
{
    float4x4 World;
    float4x4 WorldInverseTranspose;
};
ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b1);

struct Well
{
    float4x4 skeletonSpaceMatrix;
    float4x4 skeletonSpaceInverseTransposeMatrix;
};
StructuredBuffer<Well> gMatrixPalette : register(t0);

struct VertexShaderInput
{
    float4 position : POSITION0;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 worldPosition : WORLDPOSITION0;
    float3 cameraPosition : CAMERAPOSITION0;
    float4 weight : WEIGHT0;
    int4 index : INDEX0;
};

struct Skinned
{
    float4 position;
    float3 normal;
};
Skinned Skinning(VertexShaderInput input)
{
    Skinned skinned;
    
    // �ʒu�̌v�Z
    skinned.position = mul(input.position, gMatrixPalette[input.index.x].skeletonSpaceMatrix) * input.weight.x;
    skinned.position += mul(input.position, gMatrixPalette[input.index.y].skeletonSpaceMatrix) * input.weight.y;
    skinned.position += mul(input.position, gMatrixPalette[input.index.z].skeletonSpaceMatrix) * input.weight.z;
    skinned.position += mul(input.position, gMatrixPalette[input.index.w].skeletonSpaceMatrix) * input.weight.w;
    skinned.position.w = 1.0f; // 1������
    
    // �@���̌v�Z
    skinned.normal = mul(input.normal, (float3x3) gMatrixPalette[input.index.x].skeletonSpaceInverseTransposeMatrix) * input.weight.x;
    skinned.normal += mul(input.normal, (float3x3) gMatrixPalette[input.index.y].skeletonSpaceInverseTransposeMatrix) * input.weight.y;
    skinned.normal += mul(input.normal, (float3x3) gMatrixPalette[input.index.z].skeletonSpaceInverseTransposeMatrix) * input.weight.z;
    skinned.normal += mul(input.normal, (float3x3) gMatrixPalette[input.index.w].skeletonSpaceInverseTransposeMatrix) * input.weight.w;
    skinned.normal = normalize(skinned.normal); // ���K�����Ė߂��Ă�����
    
    return skinned;
}


VertexShaderOutput main(VertexShaderInput input)
{
    VertexShaderOutput output;
    
    // �܂�Skinning�v�Z���s���āASkinning�܂̒��_������ɓ����
    // �����ł̒��_��SkeletonSpace
    Skinned skinned = Skinning(input);
    
    float4x4 cameraMat = mul(gTransformationViewMatrix.view, gTransformationViewMatrix.viewProjection);
    float4x4 resultMat = mul(gTransformationMatrix.World, cameraMat);

    // Skinning���ʂ��g���ĕϊ�
    output.position = mul(skinned.position, resultMat);
    output.texcoord = input.texcoord;

    output.normal = normalize(mul(skinned.normal, (float3x3) gTransformationMatrix.WorldInverseTranspose));
    output.worldPosition = mul(skinned.position, gTransformationMatrix.World).xyz;
    
    output.cameraPosition = gTransformationViewMatrix.cameraPosition;
    
    return output;
}
