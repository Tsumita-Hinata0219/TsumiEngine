#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

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
    uint width, height;
    gTexture.GetDimensions(width, height);
    float2 uvStepSize = float2(rcp((float) width), rcp((float) height));
        
    const float2 kCenter = float2(0.5f, 0.5f); // ���S�_�B��������ɕ��ˏ�Ƀu���[��������
    const int kNumSamples = 10; // �T���v�����O���B�����قǊ��炩�����������d��
    const float kBlurWidth = 0.01f; // �ڂ����̕��B�傫���قǑ傫��
    
    // ���S����uv�ɑ΂��ĕ������v�Z
    // ���i�����Ƃ����ΒP�ʃx�N�g�������A�����ł͂����Đ��K�������A�����قǂ�艓�����T���v�����O����
    float2 direction = input.texcoord - kCenter;
    float3 outputColor = float3(0.0f, 0.0f, 0.0f);
    
    for (int sampleIndex = 0; sampleIndex < kNumSamples; ++sampleIndex)
    {
        // ���݂�uv�����قǌv�Z���������ɃT���v�����O�_��i�߂Ȃ���T���v�����O���Ă���
        float2 texcoord = input.texcoord + direction * kBlurWidth * float(sampleIndex);
        outputColor.rgb += gTexture.Sample(gSampler, texcoord).rgb;
    }
    // ���ω�����
    outputColor.rgb *= rcp(float(kNumSamples));
    
    
    PixelShaderOutput output;
    
    output.color.rgb = outputColor;
    output.color.a = 1.0f;
    
    return output;
}