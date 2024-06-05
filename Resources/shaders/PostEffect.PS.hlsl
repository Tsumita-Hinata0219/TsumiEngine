#include "PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
    int type;
    float4 color;
};
ConstantBuffer<Material> gMaterial : register(b1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    output.color = gTexture.Sample(gSampler, input.texcoord);
    
    if (gMaterial.type == 0) // None
    {
        return output;
    }
    else if (gMaterial.type == 1) // GrayScale
    {
        output.color = gTexture.Sample(gSampler, input.texcoord);
        float value = dot(output.color.rgb, float3(0.2125f, 0.7154f, 0.0721f));
        output.color.rgb = float3(value, value, value);
    }
    else if (gMaterial.type == 2) // Vignetting
    {
        // 周囲を0に、中心になるほど明るくなるように計算で調整
        float2 corrext = input.texcoord * (1.0f - input.texcoord.yx);
        // correctだけで計算すると中心の最大値が0.0625で暗すぎるのでScaleで調整。この例では16倍にして1にしてる
        float vignette = corrext.x * corrext.y * 16.0f;
        // とりあえず0.8乗でそれっぽくする
        vignette = saturate(pow(vignette, 0.8f));
        // 係数として乗算
        output.color.rgb *= vignette;
    }
    else if (gMaterial.type == 3) // Smoothing
    {
        // 周囲を0に、中心になるほど明るくなるように計算で調整
        float2 corrext = input.texcoord * (1.0f - input.texcoord.yx);
        // correctだけで計算すると中心の最大値が0.0625で暗すぎるのでScaleで調整。この例では16倍にして1にしてる
        float vignette = corrext.x * corrext.y * 16.0f;
        // とりあえず0.8乗でそれっぽくする
        vignette = saturate(pow(vignette, 0.8f));
        // 係数として乗算
        output.color.rgb *= vignette;
    }
    else if (gMaterial.type == 4) // GaussianFilter
    {
        
    }
    
    return output;
}