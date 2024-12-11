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
// PI ��
static const float PI = 3.14159265f;
// Gauss�֐�
float gauss(float x, float y, float sigma)
{
    float exponent = -(x * x + y * y) * rcp(2.0f * sigma * sigma);
    float denominator = 2.0f * PI * sigma * sigma;
    return exp(exponent) * rcp(denominator);
}
// Luminance�֐�
float Luminance(float3 v)
{
    return dot(v, float3(0.2125f, 0.7154f, 0.0721f));
}


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
    }
    else if (gMaterial.type == 5) // GaussianFilter
    {
        // kenrnel�����߂�Bweight�͌�Ŏg��
        float weight = 0.0f;
        float kernel3x3[3][3];
        
        // uvStepSize�̎Z�o
        uint width, height;
        gTexture.GetDimensions(width, height);
        float2 uvStepSize = float2(rcp((float) width), rcp((float) height));
        
        output.color.rgb = float3(0.0f, 0.0f, 0.0f);
        output.color.a = 1.0f;
        
        // gauss�֐���kernel�����߂�
        for (uint i = 0; i < 3; ++i)
        {
            for (uint j = 0; j < 3; ++j)
            {
                kernel3x3[i][j] = gauss(kINdex3x3[i][j].x, kINdex3x3[i][j].y, 2.0f);
                weight += kernel3x3[i][j];
            }
        }
        
        // ���߂�kernel���g���ABoxFilter�Ɠ�������ݍ��݂��s���BkKernel3x3�ƒ萔�ɂ��Ă����Ƃ��낪kernel3x3�ɑ��邾��
        for (uint k = 0; k < 3; ++k)
        {
            for (uint l = 0; l < 3; ++l)
            {
                // 3. ���݂�texcoord���Z�o
                float2 texcoord = input.texcoord + kINdex3x3[k][l] * uvStepSize;
              
                // 4. �F�� kernel �|���đ���
                float3 fetchColor = gTexture.Sample(gSampler, texcoord).rgb;
                output.color.rgb += fetchColor * kernel3x3[k][l];
            }
        }
        
        // ��ݍ��݌�̒l�𐳋K������B�{��gauss�֐��͑S�̂����v�����(�ϕ�)1�ɂȂ�悤�ɐ݌v����Ă���
        // �������A�����͈͉̔ʂ����Ȃ��̂ŁAkernek�l�̍��v�ł���
        //�@weight��1�ɖ����Ȃ��B�Ȃ̂ō��v��1�ɂȂ�悤�ɋt���������đS�̂��グ���Ē�������
        output.color.rgb *= rcp(weight);        
    }
    else if (gMaterial.type == 6)
    {
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
        
        //// �ω��̒������E�F�C�g�Ƃ��č����B
        //// �E�F�C�g�̌�����@�����낢��ƍl������B�Ⴆ��difference.x�����g���Ή������̃G�b�W�����o�����
        //float weight = length(difference);
        
        //// 0 ~ 1
        //weight = saturate(weight);
        
        //output.color.rgb = weight;
        //output.color.a = 1.0f;
        
        float weight = length(difference);
        
        // 0 ~ 1
        weight = saturate(weight * 6.0f);
        
        output.color.rgb = (1.0f - weight) * gTexture.Sample(gSampler, input.texcoord).rgb;
        output.color.a = 1.0f;

    }
    
    return output;
}