#include "../../GPUParticle.hlsli"


// �p�[�e�B�N���̍ő�C���X�^���X��
static const uint kParticleInstanceMax = 1024;
// �p�[�e�B�N���̗v�f
RWStructuredBuffer<ParticleCS> gParticles : register(u0);

// FreeList
RWStructuredBuffer<int> gFreeList : register(u1);
// FreeListIndex
RWStructuredBuffer<int> gFreeListIndex : register(u2);

// Emitter_Sphere
ConstantBuffer<EmitterSphere> gEmitterSphere : register(b0);
// Emitter emission related
ConstantBuffer<EmitterConfig> gEmitterConfig : register(b1);
// Random seed value
ConstantBuffer<RandomSeed> gRandomSeed : register(b2);


[numthreads(1, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    // �ˏo�����o���̂Ŏˏo
    if (gEmitterConfig.isEmitting != 0)
    {
       // Random generator
        RandomGenerator rng;
        rng.InitSeed(gRandomSeed.gameTime, (gRandomSeed.dynamicTime));
        // Set range Scale
        float3 scaleMin = float3(0.2f, 0.2f, 1.0f);
        float3 scaleMax = float3(0.6f, 0.6f, 0.6f);
        // Set translate range
        float3 translateMin = float3(-3.0f, -3.0f, -3.0f);
        float3 translateMax = float3(3.0f, 3.0f, 3.0f);
        // Set ColorRGB range
        float3 colorMin = float3(0.0f, 0.0f, 0.0f);
        float3 colorMax = float3(1.0f, 1.0f, 1.0f);
        
        // �ˏo����p�[�e�B�N����
        uint spawnCount = gEmitterConfig.spawnCount;
        
        // Number of particles
        for (uint countIndex = 0; countIndex < spawnCount; ++countIndex)
        {
            int freeListIndex;
            // FreeList��Index��1�O�ɐݒ肵�A���݂�Index���擾����
            InterlockedAdd(gFreeListIndex[0], -1, freeListIndex);
            
            // �ő吔����particle�̐������Ȃ���Ύˏo
            if (0 <= freeListIndex && freeListIndex < kParticleInstanceMax)
            {
                int particleIndex = gFreeList[freeListIndex];
                gParticles[particleIndex].scale = rng.RandomRange3D(scaleMin, scaleMax);
                gParticles[particleIndex].translate = rng.RandomRange3D(translateMin, translateMax);
                gParticles[particleIndex].color.rgb = rng.RandomRange3D(colorMin, colorMax);
                gParticles[particleIndex].color.a = 1.0f;
                
                // �����t���O�𗧂Ă�
                gParticles[particleIndex].isAlive = true;
            }
            else
            {
                // �����������Ȃ������̂ŁA���炵�Ă��܂��������Ƃɖ߂�
                InterlockedAdd(gFreeListIndex[0], 1);
                // Emit����Particle�͏����Ȃ��̂ŁA���̌㔭�����邱�Ƃ͂Ȃ�����breka���ďI��点��
                break;
            }
        }
    }
}
