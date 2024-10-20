#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

// �}�X�N�摜
Texture2D<float> gNoiseTexture : register(t1);
SamplerState gNoiseSampler : register(s1); 

struct Material
{
    float4 color;
    
};
ConstantBuffer<Material> gMaterial : register(b1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    
    // ���̃e�N�X�`������F���擾
    float4 baseColor = gTexture.Sample(gSampler, input.texcoord);
    
    // �m�C�Y�e�N�X�`������m�C�Y���擾�iUV���W�𒲐����Ă��ǂ��j
    float4 noiseColor = gNoiseTexture.Sample(gNoiseSampler, input.texcoord);
    
    // �m�C�Y�����̐F�ɓK�p�i�Ⴆ�΁A���邳�𒲐��j
    output.color = baseColor * noiseColor; // �m�C�Y����Z���ēK�p

    return output;
}