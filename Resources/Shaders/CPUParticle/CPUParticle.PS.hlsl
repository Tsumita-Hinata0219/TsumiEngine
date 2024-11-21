#include "CPUParticle.hlsli"

// テクスチャ& サンプラー
Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

// マテリアル
StructuredBuffer<Material> gMaterial : register(t1);


// Main
PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;

    // UV変換を適用
    float4 transformedUV = mul(float4(input.texCoord, 0.0f, 1.0f), gMaterial[input.instanceID].uvTransform);

    // テクスチャから色をサンプリング
    float4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
    
    // カラーの計算
    output.color = gMaterial[input.instanceID].color * textureColor;

    // アルファ値が0.9f未満なら描画をスキップ
    if (textureColor.a == 0.0f)
    {
        discard;
    }

    return output;
}

