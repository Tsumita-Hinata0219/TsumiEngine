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
    float noiseSpeed; // �m�C�Y�̓����̑���
    float noiseFrequency; // �m�C�Y�̓����̕p�x
    // �f�B�X�v���C�X�����g�}�b�v�̐ݒ�
    float2 maxDisplacement; // �ő�u�������ix: ����, y: �����j
    float time; // ���݂̎���
};
ConstantBuffer<Material> gMaterial : register(b1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

// �����_���֐��̎���
float Random(float2 uv)
{
    return frac(sin(dot(uv, float2(12.9898f, 78.233f))) * 43758.5453f);
}

float2 CalculateNoiseOffset(float2 uv, float time, float speed, float frequency)
{
    // �����_���Ȓl�𐶐����邽�߂Ƀm�C�Y���T���v�����O
    float randomX = gNoiseTexture.Sample(gNoiseSampler, uv * frequency + time * speed).r;
    float randomY = gNoiseTexture.Sample(gNoiseSampler, uv * frequency + time * speed + 100.0f).r;

    // �m�C�Y�l���X�P�[�����O
    return float2(randomX * 2.0f - 1.0f, randomY * 2.0f - 1.0f); // -1.0f����1.0f�͈̔͂ɕϊ�
}


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;

    float2 uv = input.texcoord;

    // �X�P�[�����g�p����UV���������΂��i���l���傫���قǈ������΂����悤�Ɍv�Z�j
    float2 scaledUV = (uv - 0.5f) / float2(gMaterial.noiseScale.x, gMaterial.noiseScale.y) + 0.5f;

    // �m�C�Y�I�t�Z�b�g�̌v�Z
    float2 noiseOffset = CalculateNoiseOffset(uv, gMaterial.time, gMaterial.noiseSpeed, gMaterial.noiseFrequency);
    scaledUV += noiseOffset;

    // �m�C�Y�e�N�X�`�����T���v�����O
    float noiseValue = gNoiseTexture.Sample(gNoiseSampler, scaledUV);

    // ���̃e�N�X�`�����T���v�����O
    float4 originalColor = gTexture.Sample(gSampler, uv);

    // �m�C�Y�����̐F�ɓK�p
    output.color = originalColor * noiseValue;

    return output;
}