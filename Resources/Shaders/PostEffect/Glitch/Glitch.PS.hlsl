#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

// �}�X�N�摜
Texture2D<float> gNoiseTexture : register(t1);
SamplerState gNoiseSampler : register(s1); 

struct Material
{
    float4 color;
    // �m�C�Y�ݒ�
    float2 noiseScale; // �m�C�Y�̃X�P�[���i�������΂��p�j
    float timeSpeed; // �m�C�Y�̓����̑���
    float time;
};
ConstantBuffer<Material> gMaterial : register(b1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

// �V���v���ȃm�C�Y����
float Noise(float2 uv)
{
    return frac(sin(dot(uv, float2(12.9898, 78.233))) * 43758.5453);
}

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;

    // �e�N�X�`�����W���擾
    float2 uv = input.texcoord; // �e�N�X�`�����W�����͂Ƃ��ēn����邱�Ƃ�z��

    // ���Ԃ��擾�iMaterial����擾�j
    float time = gMaterial.time * gMaterial.timeSpeed; // timeSpeed���g���Ď��Ԃ𒲐�

    // �����_���ȓ����������邽�߂̃I�t�Z�b�g
    float2 randomOffset = float2(
        Noise(uv * 10.0f + float2(time * 0.1f, 0)), // �����I�t�Z�b�g
        Noise(uv * 10.0f + float2(0, time * 0.1f)) // �����I�t�Z�b�g
    );

    // UV�Ɏ��Ԃƃ����_���ȃI�t�Z�b�g�����Z���ăm�C�Y�𓮂���
    float2 animatedNoiseUV = (uv * (1.0f / gMaterial.noiseScale)) + randomOffset * 0.1f;

    // �m�C�Y�e�N�X�`������T���v�����O
    float noiseValue = gNoiseTexture.Sample(gNoiseSampler, animatedNoiseUV).r;

    // �m�C�Y�l�����ɐF��ύX�i�����ł̓m�C�Y�l�����̂܂ܐF�Ƃ��Ďg�p�j
    output.color = gTexture.Sample(gSampler, uv) * noiseValue; // ���̃e�N�X�`���Ƀm�C�Y��K�p

    return output;
}