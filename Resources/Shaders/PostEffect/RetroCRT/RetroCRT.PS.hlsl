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
    
}

// �F�������ʂ��v�Z����֐�
float3 ChromaticAberration(float2 texcoord)
{
    
}

// �o�����䂪�݂�K������֐�
float2 ApplyBarrelDistortion(float2 texcoord)
{
    
}

// �m�C�Y���ʂ��v�Z����֐�
float NoiseEffect(float2 texcoord)
{
    
}

// �u���[�����ʂ��v�Z����֐�
float3 BloomEffect(float3 color)
{
    
}


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    
    
    
    
    return output;
}