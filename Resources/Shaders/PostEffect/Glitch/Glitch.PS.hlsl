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
    return frac(sin(dot(uv, float2(12.9898, 78.233))) * 43758.5453);
}

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;

    // UV���W�̎擾
    float2 uv = input.texcoord;

    // �X�P�[���𔽓]�i�������l���������΂����j
    float2 scaledUV = uv * (1.0f / gMaterial.noiseScale); // scale�𔽓]

    // �����_���ȃI�t�Z�b�g�𐶐�
    float randomOffsetX = Random(float2(gMaterial.time, 0.0)) * 0.1; // �����_���ȃI�t�Z�b�g��X���ɓK�p
    float randomOffsetY = Random(float2(0.0, gMaterial.time)) * 0.1; // �����_���ȃI�t�Z�b�g��Y���ɓK�p

    // �m�C�Y�̓������Ȃ��ꍇ�̓I�t�Z�b�g��0�ɂ���
    if (gMaterial.noiseFrequency > 0.0f)
    {
        // ���ԂɊ�Â����I�t�Z�b�g��ǉ�
        scaledUV += float2((gMaterial.noiseSpeed * gMaterial.time + randomOffsetX) * gMaterial.noiseFrequency,
                           (gMaterial.noiseSpeed * gMaterial.time + randomOffsetY) * gMaterial.noiseFrequency);
    }

    // �m�C�Y�e�N�X�`�����T���v�����O
    float noiseValue = gNoiseTexture.Sample(gNoiseSampler, scaledUV);

    // ���̃e�N�X�`�����T���v�����O
    float4 originalColor = gTexture.Sample(gSampler, uv);

    // �m�C�Y�����̐F�ɓK�p
    output.color = originalColor * noiseValue; // �����Ńm�C�Y���|�����킹

    return output;
}