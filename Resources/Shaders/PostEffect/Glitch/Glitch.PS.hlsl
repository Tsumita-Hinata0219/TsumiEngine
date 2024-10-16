#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
    float4 color;
    float glitchIntensity; // �O���b�`���x
    float blockScale; // �u���b�N�X�P�[��
    float noiseSpeed; // �m�C�Y���x
    float time; // ����
};
ConstantBuffer<Material> gMaterial : register(b1);

// �}�X�N�摜
Texture2D<float> gMaskTexture : register(t1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};


float random(float2 seeds)
{
    return frac(sin(dot(seeds, float2(12.9898f, 78.233f))) * 43758.5453f);
}

float blockNoise(float2 seeds)
{
    return random(floor(seeds));
}

float noiserandom(float2 seeds)
{
    return -1.0f + 2.0f * blockNoise(seeds);
}

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    // UV���W���擾
    float2 gv = input.texcoord;

    // �m�C�Y�v�Z
    float noise = blockNoise(input.texcoord.y * gMaterial.blockScale);
    noise += random(input.texcoord.x) * 0.3f;
    float2 randomValue = noiserandom(float2(input.texcoord.y, gMaterial.time * gMaterial.noiseSpeed));

    // �O���b�`�̓K�p
    gv.x += randomValue.x * gMaterial.glitchIntensity * 0.1f; // �X�P�[���𒲐�

    // �e�N�X�`�����T���v�����O
    float4 color;
    color.r = gTexture.Sample(gSampler, gv + float2(0.006f, 0.0f)).r;
    color.g = gTexture.Sample(gSampler, gv).g;
    color.b = gTexture.Sample(gSampler, gv - float2(0.008f, 0.0f)).b;
    color.a = 1.0f;

    output.color = color;

    return output;
}