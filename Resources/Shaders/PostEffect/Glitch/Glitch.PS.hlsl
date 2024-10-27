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


// ランダムなオフセットを生成
float random(float2 uv)
{
    return frac(sin(dot(uv, float2(12.9898, 78.233))) * 43758.5453);
}

float2 applyGlitchEffect(float2 uv, float intensity, float noise)
{
    // ノイズに基づいたオフセットを生成
    float offset = (random(uv) - 0.5) * intensity * noise;
    uv.x += offset; // X方向にずらす
    return uv;
}


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;

    // ノイズテクスチャから現在のUVに対応するノイズ値を取得
    float noise = gNoiseTexture.Sample(gNoiseSampler, input.texcoord);
    
    // オフセットの強度
    float intensity = 0.05;
    
    // グリッチエフェクトを適用したUV座標
    float2 glitchUV = applyGlitchEffect(input.texcoord, intensity, noise);
    
    // ずらしたUVでテクスチャをサンプリング
    output.color = gTexture.Sample(gSampler, glitchUV) * gMaterial.color;

    return output;
}