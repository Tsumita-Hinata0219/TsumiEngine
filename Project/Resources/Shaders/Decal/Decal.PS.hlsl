#include "Decal.hlsli"

// マテリアル (デカール専用なので最小限)
struct Material // 既存のMaterial構造体を流用することも可能
{
    float4 color;
    // float4x4 uvTransform; // デカールテクスチャに個別のUV変換が不要なら不要
    // uint textureIndex;
};
ConstantBuffer<Material> gMaterial : register(b0); 
Texture2D<float4> gTexture : register(t0); 

// デカール設定
ConstantBuffer<DecalSettings> gDecalSettings : register(b6);
Texture2D<float4> gDecalTexture : register(t1); // デカールテクスチャ

// サンプラー
SamplerState gSampler : register(s0);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;

    // デカールが無効なら描画をスキップ
    if (gDecalSettings.enable == 0)
    {
        discard;
    }

    // ワールド座標をデカール空間へ変換 (VSで渡し直したdecalMatrixを使う)
    // このdecalMatrixは、アプリケーション側で「デカールのワールド行列の逆行列」として設定されていると仮定
    float4 decalPos = mul(float4(input.worldPos, 1.0f), gDecalSettings.decalMatrix);

    // デカールUV座標の計算 (デカール空間のxyを0.0～1.0の範囲に正規化)
    // これにより、デカールボックスの-1.0?1.0の範囲がテクスチャの0.0?1.0にマッピングされる
    float2 decalUV = decalPos.xy * 0.5f + 0.5f;

    // デカールが範囲外であればピクセルを破棄
    // デカールボックスの範囲外に投影されたピクセルを描画しないようにします
    if (decalUV.x < 0.0f || decalUV.x > 1.0f || decalUV.y < 0.0f || decalUV.y > 1.0f ||
        decalPos.z < -1.0f || decalPos.z > 1.0f) // Z軸方向の範囲チェックも追加
    {
        discard;
    }

    // デカールテクスチャをサンプリング
    float4 decalSample = gDecalTexture.Sample(gSampler, decalUV);

    // デカールテクスチャのアルファが0なら破棄 (ひび割れの透明部分)
    if (decalSample.a == 0.0f)
    {
        discard;
    }
    
    // デカールの色をデカールテクスチャのアルファ値と強度で乗算
    output.color.rgb = gDecalSettings.decalColor.rgb * decalSample.a * gDecalSettings.decalStrength;
    output.color.a = decalSample.a; // デカールのアルファ値をそのまま使う

    return output;
}