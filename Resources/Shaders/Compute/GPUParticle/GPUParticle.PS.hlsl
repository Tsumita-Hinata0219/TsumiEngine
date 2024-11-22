#include "GPUParticle.hlsli"


// テクスチャ&サンプラー
Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

// マテリアル
//ConstantBuffer<Material> gMaterial : register(b0);
StructuredBuffer<Material> gMaterial : register(t1);

// Main
PixcelShaderOutput main(VertexShaderOutput input)
{
    PixcelShaderOutput output;
    float4 transUV = mul(float4(input.texcoord, 0.0f, 1.0f), gMaterial[input.instanceID].uvTransform);
    float4 textureColor = gTexture.Sample(gSampler, input.texcoord);
    
    if (textureColor.a == 0.0f)
    {
        discard;
    }
    output.color = textureColor;

    return output;
}