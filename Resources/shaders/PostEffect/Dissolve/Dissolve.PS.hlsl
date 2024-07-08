#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
    float4 color;
    float threshold;
};
ConstantBuffer<Material> gMaterial : register(b1);


// マスク画像
Texture2D<float> gMaskTexture : register(t1);


struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    float mask = gMaskTexture.Sample(gSampler, input.texcoord);
    // maskの値が閾値以下の場合はdiscardして抜く
    //if (mask <= gMaterial.threshold)
    //{
    //    discard;
    //}
    if (mask <= 0.5f)
    {
        discard;
    }
    
    output.color = gTexture.Sample(gSampler, input.texcoord);
    
    return output;
}