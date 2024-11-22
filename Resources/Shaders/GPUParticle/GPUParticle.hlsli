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

// ParticleÇï\Ç∑ç\ë¢ëÃ
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
