#include "CPUParticle.hlsli"


// �e�N�X�`��& �T���v���[
Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

// �}�e���A��
StructuredBuffer<Material> gMaterial : register(t1);


// Main
PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;

    // UV�ϊ���K�p
    float4 transformedUV = mul(float4(input.texCoord, 0.0f, 1.0f), gMaterial[input.instanceID].uvTransform);

    // �e�N�X�`������F���T���v�����O
    float4 textureColor = gTexture.Sample(gSampler, input.texCoord);
    
    // �J���[�̌v�Z
    output.color = textureColor;
    
    return output;
}
