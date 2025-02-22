#include "../GPUParticle.hlsli"


// テクスチャ&サンプラー
Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

// マテリアル
StructuredBuffer<Material> gMaterial : register(t1);

// Main
PixcelShaderOutput main(VertexShaderOutput input)
{
    PixcelShaderOutput output;
    float4 transUV = mul(float4(input.texCoord, 0.0f, 1.0f), gMaterial[input.instanceID].uvTransform);
    float4 textureColor = gTexture.Sample(gSampler, input.texCoord);
    
    if (textureColor.a == 0.0f)
    {
        discard;
    }
    //output.color = textureColor;
    output.color.rgb = textureColor.rgb * gMaterial[input.instanceID].color.rgb;
    output.color.a = textureColor.a * gMaterial[input.instanceID].color.a;

    return output;
}
