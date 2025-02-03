#include "../Math/Math.hlsli"


struct VertexShaderOutput
{
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD0;
    uint instanceID : INSTANCEID0;
};

struct VertexShaderInput
{
    float4 position : POSITION0;
    float2 texCoord : TEXCOORD0;
};

struct PixcelShaderOutput
{
    float4 color : SV_TARGET0;
};


// Material
struct Material
{
    float4 color;
    float4x4 uvTransform;
};

// Particleを表す構造体
struct ParticleCS
{
    float32_t3 scale;
    float32_t3 rotate;
    float32_t3 translate;
    float32_t4x4 matWorld;
    float32_t4 color;
};

// PreView
struct PreView
{
    float32_t4x4 viewProjection;
    float32_t4x4 billboardMatrix;
};

// カメラ
struct ViewProjectionMatrix
{
    float32_t4x4 view;
    float32_t4x4 projection;
    float32_t3 cameraPosition;
};

// Emitter_Sphere
struct EmitterSphere
{
    float32_t3 translate; // 位置
    float32_t radius; // 生成半径
    uint32_t count; // 生成数
    float32_t frequency; // 生成頻度
    float32_t frequencyTime; // 経過時間
    uint32_t emit; // 生成フラグ
};