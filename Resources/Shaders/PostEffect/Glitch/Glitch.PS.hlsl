#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
    float4 color;
    float2 noiseFactors; // ノイズ生成用の係数
    float2 glitchShift; // ピクセルのシフト量
    
    float glitchIntensity; // グリッチの強度
};
ConstantBuffer<Material> gMaterial : register(b1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    // テクスチャのサンプルカラーを取得
    output.color = gTexture.Sample(gSampler, input.texcoord);
    
    // テクスチャサイズを取得
    uint width, height;
    gTexture.GetDimensions(width, height);
    float2 screenSize = float2(width, height);
    
    // ピクセル位置を取得
    uint2 pixelCoord = uint2(input.texcoord * screenSize);

    // 擬似乱数でグリッチのタイミングを生成
    float randomValue = frac(sin(dot(pixelCoord, gMaterial.noiseFactors)) * 43758.5453);

    // ランダムに発生するグリッチを特定の閾値で制御
    if (randomValue < gMaterial.glitchIntensity)
    {
        // グリッチ効果：RGBチャンネルをずらす
        float3 glitchShift = float3(
            frac(sin(randomValue * 12.9898) * 43758.5453) * gMaterial.glitchShift.x,
            frac(sin(randomValue * 78.233) * 43758.5453) * gMaterial.glitchShift.y,
            frac(sin(randomValue * 57.5453) * 43758.5453) * gMaterial.glitchShift.x
        );

        // 新しいUV座標を計算して、ピクセルをシフト
        float2 shiftedUV = input.texcoord + glitchShift.xy / screenSize;
        output.color.rgb = gTexture.Sample(gSampler, shiftedUV).rgb;
    }

    // 元の色に少しだけノイズを追加（微小なデジタルノイズの効果）
    float noise = frac(sin(dot(pixelCoord, gMaterial.noiseFactors)) * 43758.5453);
    float3 noiseColor = float3(
        frac(sin(noise * 12.9898) * 43758.5453),
        frac(sin(noise * 78.233) * 43758.5453),
        frac(sin(noise * 57.5453) * 43758.5453)
    ) * 0.1; // 微小ノイズの強度
    
    output.color.rgb += noiseColor * gMaterial.glitchIntensity;

    return output;
}