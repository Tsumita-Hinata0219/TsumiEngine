#include "PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);


struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    output.color = gTexture.Sample(gSampler, input.texcoord);
    
    // ���͂�0�ɁA���S�ɂȂ�قǖ��邭�Ȃ�悤�Ɍv�Z�Œ���
    float2 corrext = input.texcoord * (1.0f - input.texcoord.yx);
    // correct�����Ōv�Z����ƒ��S�̍ő�l��0.0625�ňÂ�����̂�Scale�Œ����B���̗�ł�16�{�ɂ���1�ɂ��Ă�
    float vignette = corrext.x * corrext.y * 16.0f;
    // �Ƃ肠����0.8��ł�����ۂ�����
    vignette = saturate(pow(vignette, 0.8f));
    // �W���Ƃ��ď�Z
    output.color.rgb *= vignette;
    
    return output;
}