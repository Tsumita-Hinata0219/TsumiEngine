#include "Object3d.hlsli"
#include "MathFunc.hlsli"

struct TransformationMatrix
{
    float4x4 World;
    float4x4 WorldInverseTranspose;
};
struct ViewProjectionMatrix
{
    float4x4 view;
    float4x4 projection;
    float4x4 cameraPos;
};
struct ModelTransformMatrix
{
    float4x4 modelMatrix;
};

ConstantBuffer<TransformationMatrix> gTransformationMat : register(b0);
ConstantBuffer<ViewProjectionMatrix> gViewProjectionMat : register(b3);
ConstantBuffer<ModelTransformMatrix> gModelTransformMat : register(b4);


struct VertexShaderInput
{
    float4 position : POSITION0;
    float2 texCoord : TEXCOORD0;
    float3 normal : NORMAL0;
};


VertexShaderOutput main(VertexShaderInput input)
{
    VertexShaderOutput output;
    float mulWorld = mul(gModelTransformMat.modelMatrix, gTransformationMat.World);
    float4x4 matVP = mul(gViewProjectionMat.view, gViewProjectionMat.projection);
    float4x4 matWVP = mul(mulWorld, matVP);
    
    output.position = mul(input.position, matWVP);
    output.texCoord = input.texCoord;
    output.normal = normalize(mul(input.normal, InverseTranspose((float3x3) mulWorld)));
    output.worldPos = mul(input.position, mulWorld).xyz;
    return output;
}