#include "Sprite2d.hlsli"

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
    float3 normal : NORMAL0;
    float3 worldPos : WORLDPOSITION0;
};


VertexShaderOutput main(VertexShaderInput input)
{
    VertexShaderOutput output;
    
    // 頂点座標を行列との計算で求める
    float4x4 mat = mul(gTransformationMat.World, gViewProjectionMat.orthoGraphic);
    output.position = mul(input.position, mat);
    
    // テクスチャ座標はそのまま渡す
    output.texCoord = input.texCoord;    
    
    // 法線ベクトル
    output.normal = normalize(mul(input.normal, (float3x3) gTransformationMat.WorldInverseTranspose));
    
    // ワールド空間で位置
    output.worldPos = mul(input.position, gTransformationMat.World).wyz;    
    
    return output;
}

