#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

// マスク画像
Texture2D<float> gNoiseTexture : register(t1);
SamplerState gNoiseSampler : register(s1); 

struct Material
{
    float4 color;
    
};
ConstantBuffer<Material> gMaterial : register(b1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    
    // 元のテクスチャから色を取得
    float4 baseColor = gTexture.Sample(gSampler, input.texcoord);
    
    // ノイズテクスチャからノイズを取得（UV座標を調整しても良い）
    float4 noiseColor = gNoiseTexture.Sample(gNoiseSampler, input.texcoord);
    
    // ノイズを元の色に適用（例えば、明るさを調整）
    output.color = baseColor * noiseColor; // ノイズを乗算して適用

    return output;
}