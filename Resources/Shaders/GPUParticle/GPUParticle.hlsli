#include "../Math/Math.hlsli"
#include "../Math/Rand/RandomGenerator.hlsli"


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

struct ViewProjectionMatrix
{
    float4x4 view;
    float4x4 projection;
    float3 cameraPosition;
};

struct SphereEmitter
{
    float32_t3 translate; // 座標
    float32_t radius; // 射出半径
    uint32_t count; // 射出数
    float32_t frequency; // 射出間隔
    float32_t frequencyTime; // 射出間隔調整用時間
    uint32_t emit; // 射出許可
};

struct PerFrame
{
    float32_t time; // 時間
    float32_t deltaTime; // 1フレームの経過時間
};