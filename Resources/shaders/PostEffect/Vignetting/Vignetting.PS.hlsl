#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
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
    
    // üˆÍ‚ğ0‚ÉA’†S‚É‚È‚é‚Ù‚Ç–¾‚é‚­‚È‚é‚æ‚¤‚ÉŒvZ‚Å’²®
    float2 corrext = input.texcoord * (1.0f - input.texcoord.yx);
    // correct‚¾‚¯‚ÅŒvZ‚·‚é‚Æ’†S‚ÌÅ‘å’l‚ª0.0625‚ÅˆÃ‚·‚¬‚é‚Ì‚ÅScale‚Å’²®B‚±‚Ì—á‚Å‚Í16”{‚É‚µ‚Ä1‚É‚µ‚Ä‚é
    float vignette = corrext.x * corrext.y * 16.0f;
    // ‚Æ‚è‚ ‚¦‚¸0.8æ‚Å‚»‚ê‚Á‚Û‚­‚·‚é
    vignette = saturate(pow(vignette, 0.8f));
    // ŒW”‚Æ‚µ‚ÄæZ
    output.color.rgb *= vignette;
    
    return output;
}