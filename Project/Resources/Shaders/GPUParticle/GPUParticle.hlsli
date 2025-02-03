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

// Particle��\���\����
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

// �J����
struct ViewProjectionMatrix
{
    float32_t4x4 view;
    float32_t4x4 projection;
    float32_t3 cameraPosition;
};

// Emitter_Sphere
struct EmitterSphere
{
    float32_t3 translate; // �ʒu
    float32_t radius; // �������a
    uint32_t count; // ������
    float32_t frequency; // �����p�x
    float32_t frequencyTime; // �o�ߎ���
    uint32_t emit; // �����t���O
};