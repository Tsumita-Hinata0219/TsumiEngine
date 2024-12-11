#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
    float4 color;
    float intensity; // �r�l�b�g�̋��� (0.0 �Ŗ����A1.0 �ōő勭�x)
    float center; // ���S�ʒu (0.0 ���� 1.0 �͈̔�)
    float2 radius; // ���a
    float smoothness; // �r�l�b�g�̃X���[�Y�� (0.01 �ōd���A1.0 �Ńt���b�Ƃ�������)
    float roundness; // �r�l�b�g�̊ۂ� (0.0 �Ŏl�p�A1.0 �Ŋۂ�)
};
ConstantBuffer<Material> gMaterial : register(b1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    // �e�N�X�`������F���擾
    float4 color = gTexture.Sample(gSampler, input.texcoord);
    
    // �e�N�X�`���̒��S����̋������v�Z
    float2 center = (input.texcoord - gMaterial.center) / gMaterial.radius; // X������Y�����ňقȂ�X�P�[�����O
    float distance = length(center); // �ȉ~�`��̋������v�Z
    
    // `roundness` �Ɋ�Â��ăr�l�b�g�̌`��𒲐�
    float roundedDistance = pow(distance, 1.0f - gMaterial.roundness); // �`��𒲐�����p�����[�^
    
    // �r�l�b�g�̌��ʂ��v�Z
    float vignette = smoothstep(1.0f - gMaterial.smoothness, 1.0f, roundedDistance);

    // �r�l�b�g�̋��x���|���ĐF�𒲐�
    color.rgb *= 1.0f - gMaterial.intensity * vignette;
    
    
    output.color = color;
    
    return output;
    
}