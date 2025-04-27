#include "../Emitter.hlsli"
#include "../../GPUParticle/GPUParticle.hlsli"
#include "../../Math/Math.hlsli"
#include "../../Random/Random.hlsli"


// �p�[�e�B�N���̍ő�C���X�^���X��
static const uint kParticleInstanceMax = 1024;
// �p�[�e�B�N���̗v�f
RWStructuredBuffer<ParticleCS> gParticles : register(u0);
// �p�[�e�B�N���̐�������
RWStructuredBuffer<ParticleLifeTime> gParticleLifeTime : register(u1);

// FreeList
RWStructuredBuffer<int> gFreeList : register(u2);
// FreeListIndex
RWStructuredBuffer<int> gFreeListIndex : register(u3);

// Emitter Sphere
ConstantBuffer<SphereEmit> gEmitSphere : register(b0);
// Emitter Range
ConstantBuffer<EmitRange> gEmitRange : register(b1);
// Emitter emission related
ConstantBuffer<EmitConfig> gEmitConfig : register(b2);
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
                rng.seed3D += countIndex;
                
                // Translate
                float3 diff = rng.RandomRange3D(-gEmitSphere.radius.xyz, gEmitSphere.radius.xyz);
                gParticles[particleIndex].translate.xyz = gEmitSphere.translate.xyz + diff;
                
                // Scale
                gParticles[particleIndex].scale = rng.RandomRange3D(gEmitRange.scaleMin.xyz, gEmitRange.scaleMax.xyz);
                
                // Rotate
                gParticles[particleIndex].rotate = float3(0.0f, 0.0f, 0.0f);
                
                // MatWorld
                gParticles[particleIndex].matWorld = AffineMatrix(gParticles[particleIndex].scale, gParticles[particleIndex].rotate, gParticles[particleIndex].translate);
                
                // Color
                gParticles[particleIndex].color.rgb = rng.RandomRange3D(gEmitRange.colorMin.xyz, gEmitRange.colorMax.xyz);
                gParticles[particleIndex].color.a = 1.0f; // Alpha�͕s�����Œ�
                
                // �����t���O
                gParticles[particleIndex].isAlive = true;
                
                // ��������
                gParticleLifeTime[particleIndex].current = gEmitRange.baseLifeTime + rng.RandomRange1D(gEmitRange.lifeTimeMin, gEmitRange.lifeTimeMax);
                gParticleLifeTime[particleIndex].initTime = gParticleLifeTime[particleIndex].current;
                gParticleLifeTime[particleIndex].ratio = saturate(1.0f - gParticleLifeTime[particleIndex].current / gParticleLifeTime[particleIndex].initTime);
                
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
