#include "PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
    int type;
    float4 color;
};
ConstantBuffer<Material> gMaterial : register(b1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};


// ���͂̃e�N�Z��
static const float2 kINdex3x3[3][3] =
{
    { { -1.0f, -1.0f }, { 0.0f, -1.0f }, { 1.0f, -1.0f } },
    { { -1.0f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f } },
    { { -1.0f, 1.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } },
};
// �J�[�l��
static const float kKernel3x3[3][3] =
{
    { { 1.0f / 9.0f }, { 1.0f / 9.0f }, { 1.0f / 9.0f } },
    { { 1.0f / 9.0f }, { 1.0f / 9.0f }, { 1.0f / 9.0f } },
    { { 1.0f / 9.0f }, { 1.0f / 9.0f }, { 1.0f / 9.0f } },
};



PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    if (gMaterial.type == 0) // None
    {
        output.color = gTexture.Sample(gSampler, input.texcoord);
    }
    else if (gMaterial.type == 1) // GrayScale
    {
        output.color = gTexture.Sample(gSampler, input.texcoord);
        float value = dot(output.color.rgb, float3(0.2125f, 0.7154f, 0.0721f));
        output.color.rgb = float3(value, value, value);
    }
    else if (gMaterial.type == 2) // Sepia
    {
        output.color = gTexture.Sample(gSampler, input.texcoord);
        float3 originalColor = output.color.rgb;

        float3 sepiaColor;
        sepiaColor.r = dot(originalColor, float3(0.393, 0.769, 0.189));
        sepiaColor.g = dot(originalColor, float3(0.349, 0.686, 0.168));
        sepiaColor.b = dot(originalColor, float3(0.272, 0.534, 0.131));

        output.color.rgb = sepiaColor;
    }
    else if (gMaterial.type == 3) // Vignetting
    {
        output.color = gTexture.Sample(gSampler, input.texcoord);
        
        // ���͂�0�ɁA���S�ɂȂ�قǖ��邭�Ȃ�悤�Ɍv�Z�Œ���
        float2 corrext = input.texcoord * (1.0f - input.texcoord.yx);
        // correct�����Ōv�Z����ƒ��S�̍ő�l��0.0625�ňÂ�����̂�Scale�Œ����B���̗�ł�16�{�ɂ���1�ɂ��Ă�
        float vignette = corrext.x * corrext.y * 16.0f;
        // �Ƃ肠����0.8��ł�����ۂ�����
        vignette = saturate(pow(vignette, 0.8f));
        // �W���Ƃ��ď�Z
        output.color.rgb *= vignette;
    }
    else if (gMaterial.type == 4) // Smoothing
    {
        // 1. uvStepSize�̎Z�o
        uint width, height;
        gTexture.GetDimensions(width, height);
        float2 uvStepSize = float2(rcp((float) width), rcp((float) height));
        
        output.color.rgb = float3(0.0f, 0.0f, 0.0f);
        output.color.a = 1.0f;
        
        // 2. 3x3���[�v
        for (uint x = 0; x < 3; ++x)
        {
            for (uint y = 0; y < 3; ++y)
            {
                // 3. ���݂�texcoord���Z�o
                float2 texcoord = input.texcoord + kINdex3x3[x][y] * uvStepSize;
                
                // 4. �F�� 1/9 �|���đ���
                float3 fetchColor = gTexture.Sample(gSampler, texcoord).rgb;
                output.color.rgb += fetchColor * kKernel3x3[x][y];
            }
        }
    }
    else if (gMaterial.type == 5) // GaussianFilter
    {
        output.color = gTexture.Sample(gSampler, input.texcoord);
    }
    
    return output;
}