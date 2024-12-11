#include "../../PostEffect.hlsli"

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
    float4 color;
    float3 tone;
    float contrast;
    float saturation;
    float brightness;
    float hueShift;
    float temperature;
    float tint;
    float postExposure;
    float4 colorFilter;
    float gamma;
};
ConstantBuffer<Material> gMaterial : register(b1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};


// �F�������p�֐�
float3 AdjustHue(float3 color, float hue)
{
    float angle = radians(hue);
    float3 k = float3(0.57735, 0.57735, 0.57735);
    float cosAngle = cos(angle);
    float sinAngle = sin(angle);
    float3x3 rotationMatrix = float3x3(
        cosAngle + (1 - cosAngle) * k.x * k.x, (1 - cosAngle) * k.x * k.y - k.z * sinAngle, (1 - cosAngle) * k.x * k.z + k.y * sinAngle,
        (1 - cosAngle) * k.y * k.x + k.z * sinAngle, cosAngle + (1 - cosAngle) * k.y * k.y, (1 - cosAngle) * k.y * k.z - k.x * sinAngle,
        (1 - cosAngle) * k.z * k.x - k.y * sinAngle, (1 - cosAngle) * k.z * k.y + k.x * sinAngle, cosAngle + (1 - cosAngle) * k.z * k.z
    );
    return mul(rotationMatrix, color);
}
// �F���x�ƃe�B���g�����p�֐�
float3 AdjustTemperatureTint(float3 color, float temperature, float tint)
{
    float3 tAdjust = float3(1.0 + 0.01 * temperature, 1.0, 1.0 - 0.01 * temperature);
    float3 ttAdjust = tAdjust + float3(0.0, 0.01 * tint, 0.0);
    return color * ttAdjust;
}


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    // �e�N�X�`������F���T���v��
    output.color = gTexture.Sample(gSampler, input.texcoord);
    float3 originalColor = output.color.rgb;
   
    // �g�[������
    float3 toneAdjustedColor = originalColor * gMaterial.tone;
    
    // �R���g���X�g����
    float3 meanColor = float3(0.5, 0.5, 0.5);
    float contrastFactor = gMaterial.contrast * 0.01 + 1.0;
    float3 contrastAdjustedColor = (toneAdjustedColor - meanColor) * contrastFactor + meanColor;
    
    // ���邳���� (LDR�̂�)
#ifdef LDR
    float3 brightnessAdjustedColor = contrastAdjustedColor + gMaterial.brightness * 0.01;
#else
    float3 brightnessAdjustedColor = contrastAdjustedColor;
#endif

    // �ʓx����
    float luminance = dot(brightnessAdjustedColor, float3(0.2126, 0.7152, 0.0722)); // �P�x�̌v�Z
    float3 grayscaleColor = float3(luminance, luminance, luminance);
    float saturationFactor = gMaterial.saturation * 0.01 + 1.0;
    float3 saturationAdjustedColor = lerp(grayscaleColor, brightnessAdjustedColor, saturationFactor);


    // �F���V�t�g
    float3 hueShiftedColor = AdjustHue(saturationAdjustedColor, gMaterial.hueShift);
    
    // �F���x�ƃe�B���g����
    float3 tempTintAdjustedColor = AdjustTemperatureTint(hueShiftedColor, gMaterial.temperature, gMaterial.tint);

    // �|�X�g�I�o���� (HDR�̂�)
#ifdef HDR
    float3 postExposureAdjustedColor = tempTintAdjustedColor * pow(2.0, gMaterial.postExposure);
#else
    float3 postExposureAdjustedColor = tempTintAdjustedColor;
#endif
    
    // �F�t�B���^�[�K�p
    float3 colorFilteredColor = postExposureAdjustedColor * gMaterial.colorFilter.rgb;

    // �K���}�␳
    float3 gammaAdjustedColor = pow(colorFilteredColor, float3(1.0 / gMaterial.gamma));
    
     // �ŏI�F�̐ݒ�
    output.color.rgb = gammaAdjustedColor;
    
    return output;
}