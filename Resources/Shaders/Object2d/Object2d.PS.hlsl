#include "Object2d.hlsli"


// �}�e���A��
struct Material
{
    float4 color;
    float4x4 uvTransform;
};
ConstantBuffer<Material> gMaterial : register(b0);
Texture2D<float4> gTexture : register(t0);

// Dissolve
struct Dissolve
{
    int isActive;
    float threshold;
};
ConstantBuffer<Dissolve> gDissolve : register(b1);
Texture2D<float4> gMasktexture : register(t1);

SamplerState gSampler : register(s0);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    //float4 transformedUV = mul(float4(input.texCoord, 0.0f, 1.0f), gMaterial.uvTransform);
    //float4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);

    //output.color.rgb = gMaterial.color.rgb * textureColor.rgb;
    //output.color.a = gMaterial.color.a * textureColor.a;
    
    
    // UV�ϊ�
    float4 transformedUV = mul(float4(input.texCoord, 0.0f, 1.0f), gMaterial.uvTransform);
    float4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
    
    // �ʏ�̃J���[����
    output.color.rgb = gMaterial.color.rgb * textureColor.rgb;
    output.color.a = gMaterial.color.a * textureColor.a;
    
    // Dissolve���L�����m�F
    if (gDissolve.isActive == 1)
    {
        // Dissolve�p�̃}�X�N�摜���T���v��
        float maskValue = gMasktexture.Sample(gSampler, transformedUV.xy).r;
        
        // Dissolve��臒l���}�X�N�l���Ⴂ�ꍇ�A���̃s�N�Z����j��
        if (maskValue <= gDissolve.threshold)
        {
            discard;
        }
    }

    return output;
}