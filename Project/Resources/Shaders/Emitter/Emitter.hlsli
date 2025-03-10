
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

// �G�~�b�^�[�͈̔�
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


// Sphere Emit Data
struct SphereEmit
{
    float4 translate;
    float4 radius;
};

// Box Emit Data
struct BoxEmit
{
    float4 translate;
    float4 min;
    float4 max;
};

// Range
struct EmitRange
{
    // SR
    float4 scaleMin;
    float4 scaleMax;
    float4 rotateMin;
    float4 rotateMax;
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

// Emittion
struct EmitConfig
{
    uint spawnCount; 
    float spawnInterval; 
    float elapsedTime; 
    uint isEmitting; 
};


// Random Seed 
struct RandomSeed
{
    float gameTime;
    float dynamicTime;
};