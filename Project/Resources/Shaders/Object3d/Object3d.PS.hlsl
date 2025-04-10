#include "Object3d.hlsli"


// �}�e���A��
struct Material
{
    float4 color;
    float4x4 uvTransform;
    uint textureIndex;
};
ConstantBuffer<Material> gMaterial : register(b0);
Texture2D<float4> gTexture : register(t0);

// �J����
struct ViewProjectionMatrix
{
    float4x4 view;
    float4x4 projection;
    float4x4 orthoGraphic;
    float3 cameraPosition;
};
ConstantBuffer<ViewProjectionMatrix> gViewProjectionMat : register(b1);

// ���C�g
struct DirectionalLight
{
    float4 color;
    float3 direction;
    float intensity;
    float shininess;
    int eneble;
};
ConstantBuffer<DirectionalLight> gDirectionalLight : register(b2);

// ���}�b�v
struct Environment
{
    float scale;
    int enable;
};
ConstantBuffer<Environment> gEnvironment : register(b3);
TextureCube<float4> gEnvironmentTexture : register(t1);

// �F���Z
struct ColorAddition
{
    float4 addColor;
    float intensity;
    int enable;
};
ConstantBuffer<ColorAddition> gColorAddition : register(b4);



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
    if (textureColor.a == 0.0f)
    {
        discard;
    }
    
    // ���C�g����
    if (gDirectionalLight.eneble) // ���C�g���L���ȏꍇ
    {
        // �@���x�N�g���̌v�Z
        float3 normal = normalize(input.normal);
        
        // ���C�g�̕����x�N�g���𐳋K��
        float3 lightDir = normalize(gDirectionalLight.direction);
        
        // �����x�N�g���̌v�Z
        float3 toEye = normalize(gViewProjectionMat.cameraPosition - input.worldPos);
        
        // ���t���N�g�x�N�g���̌v�Z
        float3 reflectLight = reflect(lightDir, normal);
        
        // �n�[�t�x�N�g���̌v�Z
        float3 halfVector = normalize(lightDir + toEye);
        
        // �g�U���˂̌v�Z
        float NdotL = dot(normal, lightDir);
        float cos = pow(NdotL * 0.5f + 0.5f, 2.0f);
        float3 diffuse = gMaterial.color.rgb * textureColor.rgb * gDirectionalLight.color.rgb * cos * gDirectionalLight.intensity;
        
        // ���ʔ��˂̌v�Z
        float NdotH = dot(normal, halfVector);
        float3 specularPow = pow(saturate(NdotH), gDirectionalLight.shininess);
        float3 specular = gDirectionalLight.color.rgb * gDirectionalLight.intensity * specularPow;
       
        // �g�U���˂Ƌ��ʔ��˂̍���
        float3 finalColor = diffuse;
        
        // �e�N�X�`���̃A���t�@��0�̏ꍇ�̓s�N�Z����j��
        if (textureColor.a <= 0.5f)
        {
            discard;
        }
        
        // �F�̐ݒ�
        output.color.rgb = finalColor;
    }
    else
    {
        // ���C�e�B���O�������ȏꍇ�́A�e�N�X�`���̐F�Ƀ}�e���A���̐F���|�����킹��
        output.color.rgb = gMaterial.color.rgb * textureColor.rgb;
    }
    
    // ���}�b�v
    if (gEnvironment.enable)
    {
        float3 cameraToPos = normalize(input.worldPos - gViewProjectionMat.cameraPosition);
        float3 reflectedVector = reflect(cameraToPos, normalize(input.normal));
        float4 environmentColor = gEnvironmentTexture.Sample(gSampler, reflectedVector);
        environmentColor *= gEnvironment.scale;
        output.color.rgb += environmentColor.rgb;
    }
    
    // �F���Z
    if (gColorAddition.enable)
    {
        output.color.rgb += gColorAddition.addColor.rgb * gColorAddition.intensity;
    }

    // �A���t�@�l�̐ݒ�
    output.color.a = gMaterial.color.a * textureColor.a;

    return output;
}