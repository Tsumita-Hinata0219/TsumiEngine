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
    VertexShaderOutput output;
    
     // 頂点の位置をワールド・ビュー・プロジェクション行列で変換
    output.position = mul(input.position, gTransformationMat.WVP);
    
    // テクスチャ座標はそのまま渡す
    output.texCoord = input.texCoord;
    
    // 法線ベクトルをワールド行列の逆転置行列で変換し、正規化する
    output.normal = normalize(mul(input.normal, (float3x3) gTransformationMat.WorldInverseTranspose));
    
    return output;
}