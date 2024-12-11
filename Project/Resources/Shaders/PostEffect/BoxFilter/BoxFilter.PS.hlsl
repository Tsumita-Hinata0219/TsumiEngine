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


// ���͂̃e�N�Z��
static const float2 kINdex3x3[3][3] =
{
    { { -1.0f, -1.0f }, { 0.0f, -1.0f }, { 1.0f, -1.0f } },
    { { -1.0f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f } },
    { { -1.0f, 1.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } },
};
static const float2 kINdex5x5[5][5] =
{
    { { -2.0f, -2.0f }, { -1.0f, -2.0f }, { 0.0f, -2.0f }, { 1.0f, -2.0f }, { 2.0f, -2.0f } },
    { { -2.0f, -1.0f }, { -1.0f, -1.0f }, { 0.0f, -1.0f }, { 1.0f, -1.0f }, { 2.0f, -1.0f } },
    { { -2.0f, 0.0f }, { -1.0f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 2.0f, 0.0f } },
    { { -2.0f, 1.0f }, { -1.0f, 1.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f }, { 2.0f, 1.0f } },
    { { -2.0f, 2.0f }, { -1.0f, 2.0f }, { 0.0f, 2.0f }, { 1.0f, 2.0f }, { 2.0f, 2.0f } }
};
// �J�[�l��
static const float kKernel3x3[3][3] =
{
    { { 1.0f / 9.0f }, { 1.0f / 9.0f }, { 1.0f / 9.0f } },
    { { 1.0f / 9.0f }, { 1.0f / 9.0f }, { 1.0f / 9.0f } },
    { { 1.0f / 9.0f }, { 1.0f / 9.0f }, { 1.0f / 9.0f } },
};
static const float kKernel5x5[5][5] =
{
    { 1.0f / 25.0f, 1.0f / 25.0f, 1.0f / 25.0f, 1.0f / 25.0f, 1.0f / 25.0f },
    { 1.0f / 25.0f, 1.0f / 25.0f, 1.0f / 25.0f, 1.0f / 25.0f, 1.0f / 25.0f },
    { 1.0f / 25.0f, 1.0f / 25.0f, 1.0f / 25.0f, 1.0f / 25.0f, 1.0f / 25.0f },
    { 1.0f / 25.0f, 1.0f / 25.0f, 1.0f / 25.0f, 1.0f / 25.0f, 1.0f / 25.0f },
    { 1.0f / 25.0f, 1.0f / 25.0f, 1.0f / 25.0f, 1.0f / 25.0f, 1.0f / 25.0f }
};


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    //// 1. uvStepSize�̎Z�o
    //uint width, height;
    //gTexture.GetDimensions(width, height);
    //float2 uvStepSize = float2(rcp((float) width), rcp((float) height));
    
    //output.color.rgb = float3(0.0f, 0.0f, 0.0f);
    //output.color.a = 1.0f;
    
    //// 2. 3x3���[�v
    //for (uint x = 0; x < 3; ++x)
    //{
    //    for (uint y = 0; y < 3; ++y)
    //    {
    //        // 3. ���݂�texcoord���Z�o
    //        float2 texcoord = input.texcoord + kINdex3x3[x][y] * uvStepSize;
            
    //        // 4. �F�� 1/9 �|���đ���
    //        float3 fetchColor = gTexture.Sample(gSampler, texcoord).rgb;
    //        output.color.rgb += fetchColor * kKernel3x3[x][y];
    //    }
    //}
        
    // 1. uvStepSize�̎Z�o
    uint width, height;
    gTexture.GetDimensions(width, height);
    float2 uvStepSize = float2(rcp((float) width), rcp((float) height));
        
    output.color.rgb = float3(0.0f, 0.0f, 0.0f);
    output.color.a = 1.0f;
        
    // 2. 5x5���[�v
    for (uint x = 0; x < 5; ++x)
    {
        for (uint y = 0; y < 5; ++y)
        {
            // 3. ���݂�texcoord���Z�o
            float2 texcoord = input.texcoord + kINdex5x5[x][y] * uvStepSize;
                
            // 4. �F�� 1/25 �|���đ���
            float3 fetchColor = gTexture.Sample(gSampler, texcoord).rgb;
            output.color.rgb += fetchColor * kKernel5x5[x][y];
        }
    }
   
    
    return output;
}