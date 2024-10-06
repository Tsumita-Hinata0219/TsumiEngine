#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
    float4 color; // エッジカラー
    float scanlineStrength; // スキャンラインの強度
    int scanlineActive; // スキャンラインの有効フラグ
    float2 chromaOffsetR; // Rチャンネルの色収差オフセット (x, y)
    float2 chromaOffsetB; // Bチャンネルの色収差オフセット (x, y)
    int chromaActive; // 色収差の有効フラグ
    float barrelDistortion; // バレル歪みの強度
    int barrelActive; // バレル歪みの有効フラグ
    float noiseStrength; // ノイズの強度
    int noiseActive; // ノイズの有効フラグ
    float bloomStrength; // ブルームの強度
    int bloomActive; // ブルームの有効フラグ
    float2 resolution; // ウィンドウサイズ
    float time; // ゲーム開始時からのタイマー
};
ConstantBuffer<Material> gMaterial : register(b1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};


// スキャンライン効果を計算する関数
float ScanlineEffect(float2 texcoord)
{
    return sin(texcoord.y * gMaterial.resolution.y * 3.0f + gMaterial.time * 10.0f) * gMaterial.scanlineStrength;
}

// 色収差効果を計算する関数
float3 ChromaticAberration(float2 texcoord)
{
    float3 color;
    color.r = gTexture.Sample(gSampler, texcoord + gMaterial.chromaOffsetR).r; // Rチャンネルのずらし
    color.g = gTexture.Sample(gSampler, texcoord).g; // Gチャンネルはそのまま
    color.b = gTexture.Sample(gSampler, texcoord + gMaterial.chromaOffsetB).b; // Bチャンネルのずらし
    return color;
}

// 樽型の歪みを適用する関数（ブラウン管テレビの湾曲を再現）
float2 ApplyBarrelDistortion(float2 texcoord)
{
    // UV座標を中心基準に調整
    float2 centeredUV = (texcoord - 0.5f) * 2.0f;
    float radius = length(centeredUV); // 中心からの距離を計算

    // バレルディストーション (中央に縮むように)
    float distortionFactor = 1.0f + gMaterial.barrelDistortion * (radius * radius);
    centeredUV *= distortionFactor;

    // 正規化して元に戻す
    float2 distortedUV = centeredUV * 0.5f + 0.5f;

    // UV座標をクランプ (0.0 ~ 1.0 の範囲に制限)
    distortedUV = clamp(distortedUV, 0.0f, 1.0f);

    return distortedUV;
}

// ノイズ効果を計算する関数
float NoiseEffect(float2 texcoord)
{
   // ここで、より自然なノイズを生成
    float noise = frac(sin(dot(texcoord * gMaterial.resolution.xy * 0.1f, float2(12.9898f, 78.233f)) + gMaterial.time) * 43758.5453f);
    
    // ノイズをスケーリングして強度を調整
    float scaledNoise = (noise - 0.5f) * gMaterial.noiseStrength; // -0.5から0.5の範囲にする

    // ノイズを適用する際は、色に直接加えるのではなく、輝度を変化させる
    return scaledNoise;
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

    // 歪ませたUV座標でテクスチャをサンプリング
    float2 distortesUV = gMaterial.barrelActive ? ApplyBarrelDistortion(input.texcoord) : input.texcoord;
    output.color = gTexture.Sample(gSampler, distortesUV);

    // --- ブラウン管エフェクトの追加 ---
    float scanline = gMaterial.scanlineActive ? ScanlineEffect(input.texcoord) : 0.0f;
    float3 chromaticColor = gMaterial.chromaActive ? ChromaticAberration(distortesUV) : output.color.rgb;
    float noise = gMaterial.noiseActive ? NoiseEffect(input.texcoord) : 0.0f;
    float3 bloomColor = gMaterial.bloomActive ? BloomEffect(chromaticColor) : chromaticColor;

    // 最終的な色にスキャンラインやノイズを加える
    output.color.rgb = bloomColor + scanline + noise;
    output.color.a = 1.0f;

    return output;
}