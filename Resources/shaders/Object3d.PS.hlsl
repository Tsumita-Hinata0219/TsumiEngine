#include "Object3d.hlsli"
#include "MathFunc.hlsli"

struct Material
{
    float4 color;
    float uvTransform;
};
struct DirectionalLight
{
    float4 color; // �F(RGBA)
    float3 direction; // ���C�g�̌���
    float intensity; // �P�x
};
struct ViewProjectionMatrix
{
    float4x4 view;
    float4x4 projection;
    float4x4 cameraPos;
};

ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1);
ConstantBuffer<ViewProjectionMatrix> gViewProjectionMat : register(b3);

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);


struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    float4 transfoemdUV = mul(float4(input.texCoord, 0.0f, 1.0f), gMaterial.uvTransform);
    float4 textureColor = gTexture.Sample(gSampler, transfoemdUV.xy);
    
    // �F���s�����ȏꍇ�j������
    if (textureColor.a < 0.9f)
    {
        discard;
    }
    
    output.color.rgb = textureColor.rgb;
    output.color.a = gMaterial.color.a * textureColor.a; // ���l
    
    return output;
}