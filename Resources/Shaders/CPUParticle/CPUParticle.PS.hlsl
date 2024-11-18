#include "CPUParticle.hlsli"

// �}�e���A��
struct Material
{
    float4 color;
    float4x4 uvTransform;
};
ConstantBuffer<Material> gMaterial : register(b0);
Texture2D<float4> gTexture : register(t0);

// �J����
struct ViewProjectionMatrix
{
    float4x4 view;
    float4x4 projection;
    float3 cameraPosition;
};
ConstantBuffer<ViewProjectionMatrix> gViewProjectionMat : register(b1);

SamplerState gSampler : register(s0);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;

    // UV�ϊ���K�p
    float4 transformedUV = mul(float4(input.texCoord, 0.0f, 1.0f), gMaterial.uvTransform);

    // �e�N�X�`������F���T���v�����O
    float4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);

    // �A���t�@�l��0.9f�����Ȃ�`����X�L�b�v
    if (textureColor.a < 0.9f)
    {
        discard;
    }
    
    // �A���t�@�l�̌v�Z
    output.color.rgb = gMaterial.color.rgb * textureColor.rgb;
    output.color.a = gMaterial.color.a * textureColor.a;

    return output;
}