#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
    float4 color; // �G�b�W�J���[
    float scanlineStrength; // �X�L�������C���̋��x
    int scanlineActive; // �X�L�������C���̗L���t���O
    float2 chromaOffsetR; // R�`�����l���̐F�����I�t�Z�b�g (x, y)
    float2 chromaOffsetB; // B�`�����l���̐F�����I�t�Z�b�g (x, y)
    int chromaActive; // �F�����̗L���t���O
    float barrelDistortion; // �o�����c�݂̋��x
    int barrelActive; // �o�����c�݂̗L���t���O
    float noiseStrength; // �m�C�Y�̋��x
    int noiseActive; // �m�C�Y�̗L���t���O
    float bloomStrength; // �u���[���̋��x
    int bloomActive; // �u���[���̗L���t���O
    float2 resolution; // �E�B���h�E�T�C�Y
    float time; // �Q�[���J�n������̃^�C�}�[
};
ConstantBuffer<Material> gMaterial : register(b1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};


// �X�L�������C�����ʂ��v�Z����֐�
float ScanlineEffect(float2 texcoord)
{
    return sin(texcoord.y * gMaterial.resolution.y * 3.0f + gMaterial.time * 10.0f) * gMaterial.scanlineStrength;
}

// �F�������ʂ��v�Z����֐�
float3 ChromaticAberration(float2 texcoord)
{
    float3 color;
    color.r = gTexture.Sample(gSampler, texcoord + gMaterial.chromaOffsetR).r; // R�`�����l���̂��炵
    color.g = gTexture.Sample(gSampler, texcoord).g; // G�`�����l���͂��̂܂�
    color.b = gTexture.Sample(gSampler, texcoord + gMaterial.chromaOffsetB).b; // B�`�����l���̂��炵
    return color;
}

// �M�^�̘c�݂�K�p����֐��i�u���E���ǃe���r�̘p�Ȃ��Č��j
float2 ApplyBarrelDistortion(float2 texcoord)
{
    // UV���W�𒆐S��ɒ���
    float2 centeredUV = (texcoord - 0.5f) * 2.0f;
    float radius = length(centeredUV); // ���S����̋������v�Z

    // �o�����f�B�X�g�[�V���� (�����ɏk�ނ悤��)
    float distortionFactor = 1.0f + gMaterial.barrelDistortion * (radius * radius);
    centeredUV *= distortionFactor;

    // ���K�����Č��ɖ߂�
    float2 distortedUV = centeredUV * 0.5f + 0.5f;

    // UV���W���N�����v (0.0 ~ 1.0 �͈̔͂ɐ���)
    distortedUV = clamp(distortedUV, 0.0f, 1.0f);

    return distortedUV;
}

// �m�C�Y���ʂ��v�Z����֐�
float NoiseEffect(float2 texcoord)
{
   // �����ŁA��莩�R�ȃm�C�Y�𐶐�
    float noise = frac(sin(dot(texcoord * gMaterial.resolution.xy * 0.1f, float2(12.9898f, 78.233f)) + gMaterial.time) * 43758.5453f);
    
    // �m�C�Y���X�P�[�����O���ċ��x�𒲐�
    float scaledNoise = (noise - 0.5f) * gMaterial.noiseStrength; // -0.5����0.5�͈̔͂ɂ���

    // �m�C�Y��K�p����ۂ́A�F�ɒ��ډ�����̂ł͂Ȃ��A�P�x��ω�������
    return scaledNoise;
}

// �u���[�����ʂ��v�Z����֐�
float3 BloomEffect(float3 color)
{
    float3 bloomColor = color * 1.2f; // �P�x�̂ڂ₯
    return lerp(color, bloomColor, gMaterial.bloomStrength);
}


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;

    // �c�܂���UV���W�Ńe�N�X�`�����T���v�����O
    float2 distortesUV = gMaterial.barrelActive ? ApplyBarrelDistortion(input.texcoord) : input.texcoord;
    output.color = gTexture.Sample(gSampler, distortesUV);

    // --- �u���E���ǃG�t�F�N�g�̒ǉ� ---
    float scanline = gMaterial.scanlineActive ? ScanlineEffect(input.texcoord) : 0.0f;
    float3 chromaticColor = gMaterial.chromaActive ? ChromaticAberration(distortesUV) : output.color.rgb;
    float noise = gMaterial.noiseActive ? NoiseEffect(input.texcoord) : 0.0f;
    float3 bloomColor = gMaterial.bloomActive ? BloomEffect(chromaticColor) : chromaticColor;

    // �ŏI�I�ȐF�ɃX�L�������C����m�C�Y��������
    output.color.rgb = bloomColor + scanline + noise;
    output.color.a = 1.0f;

    return output;
}