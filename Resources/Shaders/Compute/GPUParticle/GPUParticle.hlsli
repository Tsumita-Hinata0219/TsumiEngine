struct VertexShaderOutput
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
    float4 color : COLOR0;
};

// Material
struct Material
{
    float4 color;
    float4x4 uvTransform;
};

// Particle��\���\����
struct ParticleCS
{
    float3 translate;
    float3 scale;
    float lifeTime;
    float3 velocity;
    float currentTime;
    float4 color;
};

// PreView
struct PreView
{
    float4x4 viewProjection;
    float4x4 billboardMatrix;
};