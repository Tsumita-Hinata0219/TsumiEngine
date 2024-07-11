#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
    float4 color;
    float grainAmount; // �m�C�Y�̋��x
    float2 noiseFactors; // �m�C�Y�����p�̌W��
};
ConstantBuffer<Material> gMaterial : register(b1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    // �e�N�X�`���̃T���v���J���[���擾
    output.color = gTexture.Sample(gSampler, input.texcoord);
    
    // uvStepSize�̎Z�o
    uint width, height;
    gTexture.GetDimensions(width, height);

    // �m�C�Y�̓���
    // �����_���m�C�Y�𐶐����邽�߂ɋ[���������g�p
    uint2 pixelCoord = uint2(input.texcoord * float2(width, height));
    float noise = frac(sin(dot(pixelCoord, gMaterial.noiseFactors)) * 43758.5453);
    
    // �m�C�Y�̋��x�𒲐�
    float grainAmount = gMaterial.grainAmount; // �O���C���̋��x��ݒ�i0.0����1.0�͈̔́j

    // �m�C�Y�Ɋ�Â��ĐF�𐶐�
    float3 grainColor = float3(
        frac(sin(noise * 12.9898) * 43758.5453), // R����
        frac(sin(noise * 78.233) * 43758.5453), // G����
        frac(sin(noise * 57.5453) * 43758.5453) // B����
    ) * grainAmount * gMaterial.color.rgb;
    
    // �T���v���J���[�Ƀm�C�Y��ǉ�
    output.color.rgb += grainColor;
    
    return output;
}