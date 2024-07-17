#include "Object3d.hlsli"
#include "MathFunc.hlsli"


struct Material
{
    float4 color;
    float4x4 uvTransform;
};
struct ViewProjectionMatrix
{
    float4x4 view;
    float4x4 projection;
    float3 cameraPosition;
};
struct DirectionalLight
{
    float4 color; // 色(RGBA)
    float3 direction; // ライトの向き
    float intensity; // 輝度
    float shininess; // 光沢
    bool eneble; // フラグ
};
ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<ViewProjectionMatrix> gViewProjectionMat : register(b1);
ConstantBuffer<DirectionalLight> gDirectionalLight : register(b2);

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);


struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;

    // UV変換を適用
    float4 transformedUV = mul(float4(input.texCoord, 0.0f, 1.0f), gMaterial.uvTransform);

    // テクスチャから色をサンプリング
    float4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);

    // アルファ値が0.9f未満なら描画をスキップ
    if (textureColor.a < 0.9f)
    {
        discard;
    }
    
    // ライト処理を追加
    if (gDirectionalLight.eneble) // ライトが有効な場合
    {
        // 法線ベクトルの計算
        float3 normal = normalize(input.normal);

        // ライトの方向ベクトルを正規化
        float3 lightDir = normalize(-gDirectionalLight.direction);

        // 光源の強さと色を計算
        float NdotL = max(dot(normal, lightDir), 0.0f);
        float3 diffuse = gMaterial.color.rgb * textureColor.rgb * gDirectionalLight.color.rgb * NdotL * gDirectionalLight.intensity;

        // 視線ベクトルの計算
        float3 toEye = normalize(gViewProjectionMat.cameraPosition - input.worldPos);

        // ハーフベクトルの計算
        float3 halfVector = normalize(lightDir + toEye);
        float NdotH = max(dot(normal, halfVector), 0.0f);
        float specular = pow(NdotH, gDirectionalLight.shininess);

        // 鏡面反射の計算
        float3 specularReflection = gDirectionalLight.color.rgb * gDirectionalLight.intensity * specular;

        // 拡散反射と鏡面反射の合成
        float3 finalColor = diffuse + specularReflection;

        // 色の設定
        output.color.rgb = finalColor;
    }
    else
    {
        // ライティングが無効な場合は、テクスチャの色にマテリアルの色を掛け合わせる
        output.color.rgb = gMaterial.color.rgb * textureColor.rgb;
    }
    
    // アルファ値の計算
    output.color.a = gMaterial.color.a * textureColor.a;

    return output;
}