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

// Particleを表す構造体
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

// カメラ
struct ViewProjectionMatrix
{
    float4x4 view;
    float4x4 projection;
    float3 cameraPosition;
};

// Emitterの射出に関する共通設定
struct EmitterConfig
{
    uint spawnCount; // 1回の射出で生成するパーティクル数
    float spawnInterval; // パーティクルを射出する間隔（秒）
    float elapsedTime; // 射出間隔調整用時間
    uint isEmitting; // 射出許可フラグ (0: 停止, 1: 許可)
};

// Emitter_Sphere
struct EmitterSphere
{
    uint aliveCount; // 現在生存しているパーティクル数
    float3 translate; // 位置
    float radius; // 生成半径
};

// 乱数のシード情報
struct RandomSeed
{
    float gameTime;
    float dynamicTime;
};

