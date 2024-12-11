#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

cbuffer gMaterial : register(b1)
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


// �s�N�Z���V�F�[�_�[�̏o�͍\����
struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

// �X�L�������C�����ʂ��v�Z����֐�
float ScanlineEffect(float2 texcoord)
{
    return sin(texcoord.y * resolution.y * 3.0f + time * 10.0f) * scanlineStrength;
}

// �F�������ʂ��v�Z����֐�
float3 ChromaticAberration(float2 texcoord)
{
    float3 color;
    color.r = gTexture.Sample(gSampler, texcoord + chromaOffsetR).r; // R�`�����l���̂��炵
    color.g = gTexture.Sample(gSampler, texcoord).g; // G�`�����l���͂��̂܂�
    color.b = gTexture.Sample(gSampler, texcoord + chromaOffsetB).b; // B�`�����l���̂��炵
    return color;
}

// �M�^�̘c�݂�K�p����֐��i�u���E���ǃe���r�̘p�Ȃ��Č��j
float2 ApplyBarrelDistortion(float2 texcoord)
{
    float2 centeredUV = (texcoord - 0.5f) * 2.0f;
    float radius = length(centeredUV); // ���S����̋������v�Z

    // �o�����f�B�X�g�[�V���� (�����ɏk�ނ悤��)
    float distortionFactor = 1.0f + barrelDistortion * (radius * radius);
    centeredUV *= distortionFactor;

    float2 distortedUV = centeredUV * 0.5f + 0.5f;
    distortedUV = clamp(distortedUV, 0.0f, 1.0f);

    return distortedUV;
}

// �m�C�Y���ʂ��v�Z����֐�
float NoiseEffect(float2 texcoord)
{
    float noise = frac(sin(dot(texcoord * resolution.xy * 0.1f, float2(12.9898f, 78.233f)) + time) * 43758.5453f);
    float scaledNoise = (noise - 0.5f) * noiseStrength;
    return scaledNoise;
}

// �u���[�����ʂ��v�Z����֐�
float3 BloomEffect(float3 color)
{
    float3 bloomColor = color * 1.2f; // �P�x�̂ڂ₯
    return lerp(color, bloomColor, bloomStrength);
}

// �s�N�Z���V�F�[�_�[�̃��C���֐�
PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;

    // �c�܂���UV���W�Ńe�N�X�`�����T���v�����O
    float2 distortedUV = barrelActive ? ApplyBarrelDistortion(input.texcoord) : input.texcoord;
    output.color = gTexture.Sample(gSampler, distortedUV);

    // �u���E���ǃG�t�F�N�g�̒ǉ�
    float scanline = scanlineActive ? ScanlineEffect(input.texcoord) : 0.0f;
    float3 chromaticColor = chromaActive ? ChromaticAberration(distortedUV) : output.color.rgb;
    float noise = noiseActive ? NoiseEffect(input.texcoord) : 0.0f;
    float3 bloomColor = bloomActive ? BloomEffect(chromaticColor) : chromaticColor;

    // �ŏI�I�ȐF�ɃX�L�������C����m�C�Y��������
    output.color.rgb = bloomColor + scanline + noise;
    output.color.a = 1.0f;

    return output;
}