#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

// マスク画像
Texture2D<float> gNoiseTexture : register(t1);
SamplerState gNoiseSampler : register(s1); 

struct Material
{
    float4 color;
    // ノイズ設定
    float2 noiseScale; // ノイズのスケール（引き延ばし用）
    float timeSpeed; // ノイズの動きの速さ
    float time;
};
ConstantBuffer<Material> gMaterial : register(b1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

// シンプルなノイズ生成
float Noise(float2 uv)
{
    return frac(sin(dot(uv, float2(12.9898, 78.233))) * 43758.5453);
}

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;

    // テクスチャ座標を取得
    float2 uv = input.texcoord; // テクスチャ座標が入力として渡されることを想定

    // 時間を取得（Materialから取得）
    float time = gMaterial.time * gMaterial.timeSpeed; // timeSpeedを使って時間を調整

    // ランダムな動きを加えるためのオフセット
    float2 randomOffset = float2(
        Noise(uv * 10.0f + float2(time * 0.1f, 0)), // 水平オフセット
        Noise(uv * 10.0f + float2(0, time * 0.1f)) // 垂直オフセット
    );

    // UVに時間とランダムなオフセットを加算してノイズを動かす
    float2 animatedNoiseUV = (uv * (1.0f / gMaterial.noiseScale)) + randomOffset * 0.1f;

    // ノイズテクスチャからサンプリング
    float noiseValue = gNoiseTexture.Sample(gNoiseSampler, animatedNoiseUV).r;

    // ノイズ値を元に色を変更（ここではノイズ値をそのまま色として使用）
    output.color = gTexture.Sample(gSampler, uv) * noiseValue; // 元のテクスチャにノイズを適用

    return output;
}