
struct VertexShaderOutput
{
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD0;
    float3 normal : NORMAL0;
    uint instanceID : INSTANCEID0;
};

struct VertexShaderInput
{
    float4 position : POSITION0;
    float2 texCoord : TEXCOORD0;
    float3 normal : NORMAL0;
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
    float3 scale;
    float3 rotate;
    float3 translate;
    float4x4 matWorld;
    float4 color;
    float3 velocity;
    uint isAlive;
    uint lifeTime;
};

// �p�[�e�B�N���̋����Ɋւ���\����
struct ParticleMotion
{
    float3 acceleration; // �����x
    float damping; // ���x�̌������i0.0�`1.0�j
    float3 angularVelocity; // �p���x
    float3 force; // �O��
    float drag; // ��C��R
};

// PreView
struct PreView
{
    float4x4 viewProjection;
    float4x4 billboardMatrix;
};

// �J����
struct ViewProjectionMatrix
{
    float4x4 view;
    float4x4 projection;
    float4x4 orthoGraphic;
    float3 cameraPosition;
};
