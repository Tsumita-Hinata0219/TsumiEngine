#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
    float4 color;
    float2 noiseFactors; // �m�C�Y�����p�̌W��
    float2 glitchShift; // �s�N�Z���̃V�t�g��
    
    float glitchIntensity; // �O���b�`�̋��x
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
    
    // �e�N�X�`���T�C�Y���擾
    uint width, height;
    gTexture.GetDimensions(width, height);
    float2 screenSize = float2(width, height);
    
    // �s�N�Z���ʒu���擾
    uint2 pixelCoord = uint2(input.texcoord * screenSize);

    // �[�������ŃO���b�`�̃^�C�~���O�𐶐�
    float randomValue = frac(sin(dot(pixelCoord, gMaterial.noiseFactors)) * 43758.5453);

    // �����_���ɔ�������O���b�`������臒l�Ő���
    if (randomValue < gMaterial.glitchIntensity)
    {
        // �O���b�`���ʁFRGB�`�����l�������炷
        float3 glitchShift = float3(
            frac(sin(randomValue * 12.9898) * 43758.5453) * gMaterial.glitchShift.x,
            frac(sin(randomValue * 78.233) * 43758.5453) * gMaterial.glitchShift.y,
            frac(sin(randomValue * 57.5453) * 43758.5453) * gMaterial.glitchShift.x
        );

        // �V����UV���W���v�Z���āA�s�N�Z�����V�t�g
        float2 shiftedUV = input.texcoord + glitchShift.xy / screenSize;
        output.color.rgb = gTexture.Sample(gSampler, shiftedUV).rgb;
    }

    // ���̐F�ɏ��������m�C�Y��ǉ��i�����ȃf�W�^���m�C�Y�̌��ʁj
    float noise = frac(sin(dot(pixelCoord, gMaterial.noiseFactors)) * 43758.5453);
    float3 noiseColor = float3(
        frac(sin(noise * 12.9898) * 43758.5453),
        frac(sin(noise * 78.233) * 43758.5453),
        frac(sin(noise * 57.5453) * 43758.5453)
    ) * 0.1; // �����m�C�Y�̋��x
    
    output.color.rgb += noiseColor * gMaterial.glitchIntensity;

    return output;
}