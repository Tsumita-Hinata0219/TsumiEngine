#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
    float4 color;
    float2 center; // ビネットの中心位置
    float intensity; // ビネットの強さ
    float smoothness; // スムーズさ
    float roundness; // 丸みの設定
    bool rounded; // ビネットの形状設定 (丸いビネットを使用するか)
};
ConstantBuffer<Material> gMaterial : register(b1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    // テクスチャサンプル
    output.color = gTexture.Sample(gSampler, input.texcoord);
    
    // ビネット効果の計算
    float2 uv = input.texcoord - gMaterial.center; // 中心位置を調整
    uv /= float2(gMaterial.roundness, 1.0); // 丸みを考慮
    
    // ビネットの強さとスムーズさを計算
    float vignette = length(uv) * gMaterial.intensity;
    vignette = smoothstep(1.0 - gMaterial.smoothness, 1.0, vignette);
    
    // 形状に応じたビネットの調整
    if (gMaterial.rounded)
    {
        vignette *= uv.x * uv.y * 4.0;
    }
    
    // ビネット色を適用
    output.color.rgb = lerp(output.color.rgb, gMaterial.color.rgb, vignette);
    output.color.a = gMaterial.color.a * output.color.a; // α値
    
    
    //// 周囲を0に、中心になるほど明るくなるように計算で調整
    //float2 corrext = input.texcoord * (1.0f - input.texcoord.yx);
    //// correctだけで計算すると中心の最大値が0.0625で暗すぎるのでScaleで調整。この例では16倍にして1にしてる
    //float vignette = corrext.x * corrext.y * 16.0f;
    //// とりあえず0.8乗でそれっぽくする
    //vignette = saturate(pow(vignette, 0.8f));
    //// 係数として乗算
    //output.color.rgb *= vignette;
    
    return output;
}