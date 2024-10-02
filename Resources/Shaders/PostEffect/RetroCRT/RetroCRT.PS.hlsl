#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
    float4 color; // �G�b�W�J���[
    float threshold; // �}�X�N��臒l
    float thinkness; // �G�b�W�̌���
    float scanlineStrength; // �X�L�������C���̋��x
    float chromaIntensity; // �F�����̋��x
    float barrelDistortion; // �o�����c�݂̋��x
    float noiseStrength; // �m�C�Y�̋��x
    float bloomStrength; // �u���[���̋��x
};
ConstantBuffer<Material> gMaterial : register(b1);

// �}�X�N�摜
Texture2D<float> gMaskTexture : register(t1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

// ��ʉ𑜓x�Ǝ��Ԃ�ǉ�
float2 resolution;
float time;

// �X�L�������C�����ʂ��v�Z����֐�
float ScanlineEffect(float2 texcoord)
{
    return sin(texcoord.y * resolution.y * 3.0f + time * 10.0f) * gMaterial.scanlineStrength;
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
    float noise = frac(sin(dot(texcoord * resolution.xy, float2(12.9898f, 78.233f)) + time) * 43758.5453f);
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
    
    float mask = gMaskTexture.Sample(gSampler, input.texcoord);
    if (mask <= gMaterial.threshold)
    {
        discard;
    }
    
    // �G�b�W����
    float edge = 1.0f - smoothstep(gMaterial.threshold, gMaterial.threshold + gMaterial.thinkness, mask);
    output.color = gTexture.Sample(gSampler, input.texcoord);
    output.color.rgb += edge * gMaterial.color.rgb;
    
    // --- �u���E���ǃG�t�F�N�g�̒ǉ� ---
    float scanline = ScanlineEffect(input.texcoord);
    float3 chromaticColor = ChromaticAberration(input.texcoord);
    float2 distortesUV = ApplyBarrelDistortion(input.texcoord);
    float noise = NoiseEffect(input.texcoord);
    float3 bloomColor = BloomEffect(chromaticColor);    
    
    // �ŏI�I�ȐF�ɃX�L�������C�g�m�C�Y��������
    output.color.rgb = bloomColor + scanline + noise;
    output.color.a = 1.0f;
    
    return output;
}