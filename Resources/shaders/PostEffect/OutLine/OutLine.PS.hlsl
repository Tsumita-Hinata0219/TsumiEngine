#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);
//Texture2D<float> gDepthTexture : register(t1);
//SamplerState gSamplerPoint : register(s1);

struct Material
{
    float4 color;
    float4x4 projectionInverse;
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
static const float kPrewittHorizontalKernel[3][3] =
{
    { -1.0f / 6.0f, 0.0f, 1.0f / 6.0f },
    { -1.0f / 6.0f, 0.0f, 1.0f / 6.0f },
    { -1.0f / 6.0f, 0.0f, 1.0f / 6.0f },
};
static const float kPrewittVerticalKernel[3][3] =
{
    { -1.0f / 6.0f, -1.0f / 6.0f, -1.0f / 6.0f },
    { 0.0f, 0.0f, 0.0f },
    { 1.0f / 6.0f, 1.0f / 6.0f, 1.0f / 6.0f },
};

// Luminance�֐�
float Luminance(float3 v)
{
    return dot(v, float3(0.2125f, 0.7154f, 0.0721f));
}


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    // ������������������ ���ꂽ�Ԃ񔒍��̂��
    //// �ω��̒������E�F�C�g�Ƃ��č����B
    //// �E�F�C�g�̌�����@�����낢��ƍl������B�Ⴆ��difference.x�����g���Ή������̃G�b�W�����o�����
    //float weight = length(difference);
    
    //// 0 ~ 1
    //weight = saturate(weight);
    
    //output.color.rgb = weight;
    //output.color.a = 1.0f;
    
    
    
    // ������������������ ����͋P�x�x�[�X��OutLine
    // uvStepSize�̎Z�o
    uint width, height;
    gTexture.GetDimensions(width, height);
    float2 uvStepSize = float2(rcp((float) width), rcp((float) height));
        
    // �c�����ꂼ��̏�ݍ��݂̌��ʂ��i�[����
    float2 difference = float2(0.0f, 0.0f);
        
    // �F���P�x�ɕϊ����āA��ݍ��݂��s���Ă����B����Filter�p��kernel�ɂȂ��Ă���̂ŁA��邱�Ǝ��͍̂��܂ł̏�ݍ��݂Ɠ���
    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            float2 texCoord = input.texcoord + kINdex3x3[x][y] * uvStepSize;
            float3 fetchColor = gTexture.Sample(gSampler, texCoord).rgb;
            float luminance = Luminance(fetchColor);
            difference.x += luminance * kPrewittHorizontalKernel[x][y];
            difference.y += luminance * kPrewittVerticalKernel[x][y];
        }
    }
        
    float weight = length(difference);
        
        // 0 ~ 1
    weight = saturate(weight * 6.0f);
        
    output.color.rgb = (1.0f - weight) * gTexture.Sample(gSampler, input.texcoord).rgb;
    output.color.a = 1.0f;
    
    
    //// ���o�Ώۂ�Depth�ɕύX����
    //// uvStepSize�̎Z�o
    //uint width, height;
    //gTexture.GetDimensions(width, height);
    //float2 uvStepSize = float2(rcp((float) width), rcp((float) height));
        
    //// �c�����ꂼ��̏�ݍ��݂̌��ʂ��i�[����
    //float2 difference = float2(0.0f, 0.0f);
        
    //// �F���P�x�ɕϊ����āA��ݍ��݂��s���Ă����B����Filter�p��kernel�ɂȂ��Ă���̂ŁA��邱�Ǝ��͍̂��܂ł̏�ݍ��݂Ɠ���
    //for (int x = 0; x < 3; ++x)
    //{
    //    for (int y = 0; y < 3; ++y)
    //    {
    //        float2 texCoord = input.texcoord + kINdex3x3[x][y] * uvStepSize;
    //        float ndcDepth = gDepthTexture.Sample(gSamplerPoint, texCoord);
    //        // NDC -> View�BP^{-1}�ɂ�����x��y��zw�ɉe����^���Ȃ��̂łȂ�ł��ǂ��B�Ȃ̂ŁA�킴�킴�s���n���Ȃ��Ă����B
    //        float4 viewSpace = mul(float4(0.0f, 0.0f, ndcDepth, 1.0f), gMaterial.projectionInverse);
    //        float viewZ = viewSpace.z * rcp(viewSpace.w); // �������W�n����f�J���g���W�n�֕ϊ�
    //        difference.x += viewZ * kPrewittHorizontalKernel[x][y];
    //        difference.y += viewZ * kPrewittVerticalKernel[x][y];
    //    }
    //}
        
    //float weight = length(difference);
        
    //    // 0 ~ 1
    //weight = saturate(weight);
        
    //output.color.rgb = (1.0f - weight) * gDepthTexture.Sample(gSampler, input.texcoord);
    //output.color.a = 1.0f;
    
    return output;
}