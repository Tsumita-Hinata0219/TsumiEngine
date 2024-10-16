#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
    float4 color;
    float grainAmount; // ノイズの強度
    float2 noiseFactors; // ノイズ生成用の係数
    float displacementStrength; // ディスプレイスメントの強さ
    float scanlineStrength; // スキャンラインの強さ
    float aberrationStrength; // 色収差の強さ
};
ConstantBuffer<Material> gMaterial : register(b1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};


// フラクタルノイズ
float FractalNoise(float2 uv)
{
    float noise = frac(sin(dot(uv, float2(12.9898, 78.233))) * 43758.5453);
    return noise;
}

// ディスプレイスメントマップ
float2 ApplyDisplacement(float2 uv, float displacementStrength)
{
    float noise = FractalNoise(uv * 10.0f); // フラクタルノイズの強さを調整
    float2 displacement = (noise - 0.5) * displacementStrength;
    return uv + displacement;
}

// スキャンライン
float ScanlineEffect(float2 uv, float scanlineStrength)
{
    float scanline = sin(uv.y * 800.0) * scanlineStrength;
    return scanline;
}
float3 ApplyScanlines(float3 color, float2 uv, float scanlineStrength)
{
    float scanline = ScanlineEffect(uv, scanlineStrength);
    return color * (1.0 - scanline);
}

// RGB分離(色収差)
float3 ApplyChromaticAberration(float2 uv, float aberrationStrength)
{
    // R, G, B のそれぞれのUV座標をずらす
    float3 color;
    color.r = gTexture.Sample(gSampler, uv + aberrationStrength).r;
    color.g = gTexture.Sample(gSampler, uv).g;
    color.b = gTexture.Sample(gSampler, uv - aberrationStrength).b;
    
    return color;
}


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
   // UVディスプレイスメントを適用
    float2 displacedUV = ApplyDisplacement(input.texcoord, gMaterial.displacementStrength);
    
    // テクスチャサンプル
    output.color = gTexture.Sample(gSampler, displacedUV);

    // スキャンラインの適用
    output.color.rgb = ApplyScanlines(output.color.rgb, input.texcoord, gMaterial.scanlineStrength);

    // 色収差の適用
    output.color.rgb = ApplyChromaticAberration(displacedUV, gMaterial.aberrationStrength);

    // ノイズの適用
    uint width, height;
    gTexture.GetDimensions(width, height);
    uint2 pixelCoord = uint2(displacedUV * float2(width, height));
    float noise = frac(sin(dot(pixelCoord, gMaterial.noiseFactors)) * 43758.5453);
    
    float grainAmount = gMaterial.grainAmount;
    float3 grainColor = float3(
        frac(sin(noise * 12.9898) * 43758.5453),
        frac(sin(noise * 78.233) * 43758.5453),
        frac(sin(noise * 57.5453) * 43758.5453)
    ) * grainAmount * gMaterial.color.rgb;
    
    output.color.rgb += grainColor;

    return output;
}