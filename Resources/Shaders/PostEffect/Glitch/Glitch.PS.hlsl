#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
    float4 color;
    float glitchIntensity; // グリッチ強度
    float blockScale; // ブロックスケール
    float noiseSpeed; // ノイズ速度
    float time; // 時間
};
ConstantBuffer<Material> gMaterial : register(b1);

// マスク画像
Texture2D<float> gMaskTexture : register(t1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};


float random(float2 seeds)
{
    return frac(sin(dot(seeds, float2(12.9898f, 78.233f))) * 43758.5453f);
}

float blockNoise(float2 seeds)
{
    return random(floor(seeds));
}

float noiserandom(float2 seeds)
{
    return -1.0f + 2.0f * blockNoise(seeds);
}

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    // UV座標を取得
    float2 gv = input.texcoord;

    // ノイズ計算
    float noise = blockNoise(input.texcoord.y * gMaterial.blockScale);
    noise += random(input.texcoord.x) * 0.3f;
    float2 randomValue = noiserandom(float2(input.texcoord.y, gMaterial.time * gMaterial.noiseSpeed));

    // グリッチの適用
    gv.x += randomValue.x * gMaterial.glitchIntensity * 0.1f; // スケールを調整

    // テクスチャをサンプリング
    float4 color;
    color.r = gTexture.Sample(gSampler, gv + float2(0.006f, 0.0f)).r;
    color.g = gTexture.Sample(gSampler, gv).g;
    color.b = gTexture.Sample(gSampler, gv - float2(0.008f, 0.0f)).b;
    color.a = 1.0f;

    output.color = color;

    return output;
}