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
    
}

// 色収差効果を計算する関数
float3 ChromaticAberration(float2 texcoord)
{
    
}

// バレルゆがみを適応する関数
float2 ApplyBarrelDistortion(float2 texcoord)
{
    
}

// ノイズ効果を計算する関数
float NoiseEffect(float2 texcoord)
{
    
}

// ブルーム効果を計算する関数
float3 BloomEffect(float3 color)
{
    
}


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    
    
    
    
    return output;
}