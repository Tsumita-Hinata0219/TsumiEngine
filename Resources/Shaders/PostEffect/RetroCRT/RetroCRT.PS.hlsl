#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
    float4 color; // エッジカラー
    float threshold; // マスクの閾値
    float thinkness; // エッジの厚さ
    float scanlineStrength; // スキャンラインの強度
    float chromaIntensity; // 色収差の強度
    float barrelDistortion; // バレル歪みの強度
    float noiseStrength; // ノイズの強度
    float bloomStrength; // ブルームの強度
};
ConstantBuffer<Material> gMaterial : register(b1);

// マスク画像
Texture2D<float> gMaskTexture : register(t1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

// 画面解像度と時間を追加
float2 resolution;
float time;

// スキャンライン効果を計算する関数
float ScanlineEffect(float2 texcoord)
{
    return sin(texcoord.y * resolution.y * 3.0f + time * 10.0f) * gMaterial.scanlineStrength;
}

// 色収差効果を計算する関数
float3 ChromaticAberration(float2 texcoord)
{
    float2 chromaOffsetR = float2(gMaterial.chromaIntensity, 0.0f);
    float2 chromaOffsetB = float2(-gMaterial.chromaIntensity, 0.0f);
    float3 color;
    color.r = gTexture.Sample(gSampler, texcoord + chromaOffsetR).r;
    color.g = gTexture.Sample(gSampler, texcoord).g;
    color.b = gTexture.Sample(gSampler, texcoord + chromaOffsetB).b;
    return color;
}

// バレルゆがみを適応する関数
float2 ApplyBarrelDistortion(float2 texcoord)
{
    float2 centeredUV = (texcoord - 0.5f) * 2.0f;
    float radius = length(centeredUV);
    float barrelDistorion = 1.0f + gMaterial.barrelDistortion * pow(radius, 2.0f);
    centeredUV /= barrelDistorion;
    return centeredUV * 0.5f + 0.5f; // 正規化
}

// ノイズ効果を計算する関数
float NoiseEffect(float2 texcoord)
{
    float noise = frac(sin(dot(texcoord * resolution.xy, float2(12.9898f, 78.233f)) + time) * 43758.5453f);
    return (noise - 0.5f) * gMaterial.noiseStrength;
}

// ブルーム効果を計算する関数
float3 BloomEffect(float3 color)
{
    float3 bloomColor = color * 1.2f; // 輝度のぼやけ
    return lerp(color, bloomColor, gMaterial.bloomStrength);
}


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    float mask = gMaskTexture.Sample(gSampler, input.texcoord);
    if (mask <= gMaterial.threshold)
    {
        discard;
    }
    
    // エッジ効果
    float edge = 1.0f - smoothstep(gMaterial.threshold, gMaterial.threshold + gMaterial.thinkness, mask);
    output.color = gTexture.Sample(gSampler, input.texcoord);
    output.color.rgb += edge * gMaterial.color.rgb;
    
    // --- ブラウン管エフェクトの追加 ---
    float scanline = ScanlineEffect(input.texcoord);
    float3 chromaticColor = ChromaticAberration(input.texcoord);
    float2 distortesUV = ApplyBarrelDistortion(input.texcoord);
    float noise = NoiseEffect(input.texcoord);
    float3 bloomColor = BloomEffect(chromaticColor);    
    
    // 最終的な色にスキャンライトノイズを加える
    output.color.rgb = bloomColor + scanline + noise;
    output.color.a = 1.0f;
    
    return output;
}