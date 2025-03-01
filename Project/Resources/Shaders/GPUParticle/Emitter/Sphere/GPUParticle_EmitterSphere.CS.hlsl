#include "../../GPUParticle.hlsli"


// �p�[�e�B�N���ő�C���X�^���X��
static const uint kParticleInstanceMax = 1024;

// �p�[�e�B�N���̗v�f
RWStructuredBuffer<ParticleCS> gParticles : register(u0);

// FreeList
RWStructuredBuffer<int> gFreeList : register(u1);
// FreeList��Index
RWStructuredBuffer<int> gFreeListIndex : register(u2);


// EmitterSphere�̐ݒ�
ConstantBuffer<EmitterSphere> gEmitterSphere : register(b0);

// Emitter�̎ˏo�֘A
ConstantBuffer<EmitterConfig> gEmitterConfig : register(b1);

// Random��Seed�̒l
ConstantBuffer<RandomSeed> gRandomSeed : register(b2);


[numthreads(1, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    // �ˏo�����o���̂Ŏˏo
    if (gEmitterConfig.isEmitting != 0)
    {
        // ����������
        RandomGenerator rng;
        rng.InitSeed(gRandomSeed.gameTime, (gRandomSeed.dynamicTime));
        // �͈͂̐ݒ�
        // �X�P�[��
        float3 scaleMin = float3(0.2f, 0.2f, 1.0f);
        float3 scaleMax = float3(0.6f, 0.6f, 0.6f);
        // ���W
        float3 translateMin = float3(-3.0f, -3.0f, -3.0f);
        float3 translateMax = float3(3.0f, 3.0f, 3.0f);
        // �J���[ RGB
        float3 colorMin = float3(0.0f, 0.0f, 0.0f);
        float3 colorMax = float3(1.0f, 1.0f, 1.0f);
        
        // ���݂̐������Ă���p�[�e�B�N����
        uint spawnCount = gEmitterConfig.spawnCount;
        
        //��
        for (uint countIndex = 0; countIndex < spawnCount; ++countIndex)
        {
            int freeListIndex;
            InterlockedAdd(gFreeListIndex[0], -1, freeListIndex);
            
            // �ő吔����particle�̐������Ȃ���Ύˏo�\
            if (0 <= freeListIndex && freeListIndex < kParticleInstanceMax)
            {
                int particleIndex = gFreeList[freeListIndex];
                // �J�E���g��Particle���ˏo����
                gParticles[particleIndex].scale = rng.RandomRange3D(scaleMin, scaleMax);
                gParticles[particleIndex].translate = rng.RandomRange3D(translateMin, translateMax);
                gParticles[particleIndex].color.rgb = rng.RandomRange3D(colorMin, colorMax);
                gParticles[particleIndex].color.a = 1.0f;
                
                // �����t���O�𗧂Ă�
                gParticles[particleIndex].isAlive = true;
                
            }
        }
    }
}
