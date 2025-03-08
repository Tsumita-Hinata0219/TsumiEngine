#include "../Math/Math.hlsli"
#include "../Random/Random.hlsli"


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
    float3 scale;
    float3 rotate;
    float3 translate;
    float4x4 matWorld;
    float4 color;
    uint isAlive;
    uint lifeTime;
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
    float3 cameraPosition;
};

// Emitter�̎ˏo�Ɋւ��鋤�ʐݒ�
struct EmitterConfig
{
    uint spawnCount; // 1��̎ˏo�Ő�������p�[�e�B�N����
    float spawnInterval; // �p�[�e�B�N�����ˏo����Ԋu�i�b�j
    float elapsedTime; // �ˏo�Ԋu�����p����
    uint isEmitting; // �ˏo���t���O (0: ��~, 1: ����)
};

// Emitter_Sphere
struct EmitterSphere
{
    uint aliveCount; // ���ݐ������Ă���p�[�e�B�N����
    float3 translate; // �ʒu
    float radius; // �������a
};

// �����̃V�[�h���
struct RandomSeed
{
    float gameTime;
    float dynamicTime;
};

