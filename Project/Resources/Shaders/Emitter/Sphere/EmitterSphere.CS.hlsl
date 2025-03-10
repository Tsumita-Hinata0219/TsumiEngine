#include "../Emitter.hlsli"
#include "../../GPUParticle/GPUParticle.hlsli"
#include "../../Math/Math.hlsli"
#include "../../Random/Random.hlsli"


// �p�[�e�B�N���̍ő�C���X�^���X��
static const uint kParticleInstanceMax = 1024;
// �p�[�e�B�N���̗v�f
RWStructuredBuffer<ParticleCS> gParticles : register(u0);

// FreeList
RWStructuredBuffer<int> gFreeList : register(u1);
// FreeListIndex
RWStructuredBuffer<int> gFreeListIndex : register(u2);

// Emitter Sphere
ConstantBuffer<EmitterSphere> gEmitSphere : register(b0);
// Emitter Range
ConstantBuffer<EmitterRange> gEmitRange : register(b1);
// Emitter emission related
ConstantBuffer<EmitterConfig> gEmitConfig : register(b2);
// Random seed value
ConstantBuffer<RandomSeed> gRandomSeed : register(b3);


[numthreads(1, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    // �ˏo�����o���̂Ŏˏo
    if (gEmitConfig.isEmitting != 0)
    {
        // Random generator
        RandomGenerator rng;
        rng.InitSeed(gRandomSeed.gameTime, (gRandomSeed.dynamicTime + DTid.x * 0.5f));
        
        // Number of particles
        for (uint countIndex = 0; countIndex < gEmitConfig.spawnCount; ++countIndex)
        {
            int freeListIndex;
            // FreeList��Index��1�O�ɐݒ肵�A���݂�Index���擾����
            InterlockedAdd(gFreeListIndex[0], -1, freeListIndex);
            
            // �ő吔����particle�̐������Ȃ���Ύˏo
            if (0 <= freeListIndex && freeListIndex < kParticleInstanceMax)
            {
                int particleIndex = gFreeList[freeListIndex];
                // SRT
                gParticles[particleIndex].scale = rng.RandomRange3D(gEmitRange.scaleMin.xyz, gEmitRange.scaleMax.xyz);
                gParticles[particleIndex].rotate = float3(0.0f, 0.0f, 0.0f);
                gParticles[particleIndex].translate = rng.RandomRange3D(gEmitRange.translateMin.xyz, gEmitRange.translateMax.xyz);
                gParticles[particleIndex].matWorld = AffineMatrix(gParticles[particleIndex].scale, gParticles[particleIndex].rotate, gParticles[particleIndex].translate);
                
                // Color
                gParticles[particleIndex].color.rgb = rng.RandomRange3D(gEmitRange.colorMin.xyz, gEmitRange.colorMax.xyz);
                gParticles[particleIndex].color.a = 1.0f; // Alpha�͕s�����Œ�
                
                // �����t���O
                gParticles[particleIndex].isAlive = true;
                
                // ��������
                gParticles[particleIndex].lifeTime = gEmitRange.baseLifeTime + rng.RandomRange1D(gEmitRange.lifeTimeMin, gEmitRange.lifeTimeMax);

                // Velocity
                gParticles[particleIndex].velocity = rng.RandomRange3D(gEmitRange.velocityMin.xyz, gEmitRange.velocityMax.xyz);

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
