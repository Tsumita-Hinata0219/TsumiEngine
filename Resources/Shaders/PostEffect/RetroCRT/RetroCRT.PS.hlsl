#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
    float4 color; // �G�b�W�J���[
    float scanlineStrength; // �X�L�������C���̋��x
    int scanlineActive; // �X�L�������C���̗L���t���O
    float chromaIntensity; // �F�����̋��x
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
    float2 chromaOffsetR = float2(gMaterial.chromaIntensity, 0.0f);
    float2 chromaOffsetB = float2(-gMaterial.chromaIntensity, 0.0f);
    float3 color;
    color.r = gTexture.Sample(gSampler, texcoord + chromaOffsetR).r;
    color.g = gTexture.Sample(gSampler, texcoord).g;
    color.b = gTexture.Sample(gSampler, texcoord + chromaOffsetB).b;
    return color;
}

// �o�����䂪�݂�K������֐�
float2 ApplyBarrelDistortion(float2 texcoord)
{
    float2 centeredUV = (texcoord - 0.5f) * 2.0f;
    float radius = length(centeredUV);
    float barrelDistorion = 1.0f + gMaterial.barrelDistortion * pow(radius, 2.0f);
    centeredUV /= barrelDistorion;
    return centeredUV * 0.5f + 0.5f; // ���K��
}

// �m�C�Y���ʂ��v�Z����֐�
float NoiseEffect(float2 texcoord)
{
    float noise = frac(sin(dot(texcoord * gMaterial.resolution.xy, float2(12.9898f, 78.233f)) + gMaterial.time) * 43758.5453f);
    return (noise - 0.5f) * gMaterial.noiseStrength;
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