#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
    float4 color;
    float2 center; // �r�l�b�g�̒��S�ʒu
    float intensity; // �r�l�b�g�̋���
    float smoothness; // �X���[�Y��
    float roundness; // �ۂ݂̐ݒ�
    bool rounded; // �r�l�b�g�̌`��ݒ� (�ۂ��r�l�b�g���g�p���邩)
};
ConstantBuffer<Material> gMaterial : register(b1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    // �e�N�X�`���T���v��
    output.color = gTexture.Sample(gSampler, input.texcoord);
    
    // �r�l�b�g���ʂ̌v�Z
    float2 uv = input.texcoord - gMaterial.center; // ���S�ʒu�𒲐�
    uv /= float2(gMaterial.roundness, 1.0); // �ۂ݂��l��
    
    // �r�l�b�g�̋����ƃX���[�Y�����v�Z
    float vignette = length(uv) * gMaterial.intensity;
    vignette = smoothstep(1.0 - gMaterial.smoothness, 1.0, vignette);
    
    // �`��ɉ������r�l�b�g�̒���
    if (gMaterial.rounded)
    {
        vignette *= uv.x * uv.y * 4.0;
    }
    
    // �r�l�b�g�F��K�p
    output.color.rgb = lerp(output.color.rgb, gMaterial.color.rgb, vignette);
    output.color.a = gMaterial.color.a * output.color.a; // ���l
    
    
    //// ���͂�0�ɁA���S�ɂȂ�قǖ��邭�Ȃ�悤�Ɍv�Z�Œ���
    //float2 corrext = input.texcoord * (1.0f - input.texcoord.yx);
    //// correct�����Ōv�Z����ƒ��S�̍ő�l��0.0625�ňÂ�����̂�Scale�Œ����B���̗�ł�16�{�ɂ���1�ɂ��Ă�
    //float vignette = corrext.x * corrext.y * 16.0f;
    //// �Ƃ肠����0.8��ł�����ۂ�����
    //vignette = saturate(pow(vignette, 0.8f));
    //// �W���Ƃ��ď�Z
    //output.color.rgb *= vignette;
    
    return output;
}