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
    float noiseSpeed; // ノイズの動きの速さ
    float noiseFrequency; // ノイズの動きの頻度
    float time; // 現在の時間
};
ConstantBuffer<Material> gMaterial : register(b1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

// ランダム関数の実装
float Random(float2 uv)
{
    return frac(sin(dot(uv, float2(12.9898, 78.233))) * 43758.5453);
}

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;

    // UV座標の取得
    float2 uv = input.texcoord;

    // スケールを反転（小さい値が引き延ばされる）
    float2 scaledUV = uv * (1.0f / gMaterial.noiseScale); // scaleを反転

    // ランダムなオフセットを生成
    float randomOffsetX = Random(float2(gMaterial.time, 0.0)) * 0.1; // ランダムなオフセットをX軸に適用
    float randomOffsetY = Random(float2(0.0, gMaterial.time)) * 0.1; // ランダムなオフセットをY軸に適用

    // ノイズの動きがない場合はオフセットを0にする
    if (gMaterial.noiseFrequency > 0.0f)
    {
        // 時間に基づいたオフセットを追加
        scaledUV += float2((gMaterial.noiseSpeed * gMaterial.time + randomOffsetX) * gMaterial.noiseFrequency,
                           (gMaterial.noiseSpeed * gMaterial.time + randomOffsetY) * gMaterial.noiseFrequency);
    }

    // ノイズテクスチャをサンプリング
    float noiseValue = gNoiseTexture.Sample(gNoiseSampler, scaledUV);

    // 元のテクスチャをサンプリング
    float4 originalColor = gTexture.Sample(gSampler, uv);

    // ノイズを元の色に適用
    output.color = originalColor * noiseValue; // ここでノイズを掛け合わせ

    return output;
}