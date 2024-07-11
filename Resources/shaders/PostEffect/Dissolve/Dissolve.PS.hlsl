#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
    float4 color;
    float threshold;
    float thinkness;
};
ConstantBuffer<Material> gMaterial : register(b1);


// �}�X�N�摜
Texture2D<float> gMaskTexture : register(t1);


struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    float mask = gMaskTexture.Sample(gSampler, input.texcoord);
    // mask�̒l��臒l�ȉ��̏ꍇ��discard���Ĕ���
    if (mask <= gMaterial.threshold)
    {
        discard;
    }
    
    
    // �G�b�W�쐬�BEdge���ۂ����Z�o
    float edge = 1.0f - smoothstep(gMaterial.threshold, gMaterial.threshold + gMaterial.thinkness, mask);
    output.color = gTexture.Sample(gSampler, input.texcoord);
    // Edge���ۂ����w�肵���F�����Z
    output.color.rgb += edge * gMaterial.color.rgb;   
     
    return output;
}