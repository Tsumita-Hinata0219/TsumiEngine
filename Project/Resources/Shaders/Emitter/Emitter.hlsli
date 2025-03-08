
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

// エミッターの範囲
struct EmitterRange
{
    // SRT
    float4 scaleMin;
    float4 scaleMax;
    float4 rotateMin;
    float4 rotateMax;
    float4 translateMin;
    float4 translateMax;
    // Color
    float4 colorMin;
    float4 colorMax;
    // Motion
    float4 velocityMin;
    float4 velocityMax;
    // Life
    float baseLifeTime;
    float lifeTimeMin;
    float lifeTimeMax;
};

// 乱数のシード情報
struct RandomSeed
{
    float gameTime;
    float dynamicTime;
};

