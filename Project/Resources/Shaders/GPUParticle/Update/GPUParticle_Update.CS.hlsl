#include "../GPUParticle.hlsli"
#include "../../Math/Math.hlsli"
#include "../../Random/Random.hlsli"

static const uint kParticleInstanceMax = 1024;

RWStructuredBuffer<ParticleCS> gParticles : register(u0);
RWStructuredBuffer<ParticleLifeTime> gLifeTime : register(u1);
RWStructuredBuffer<int> gFreeList : register(u2);
RWStructuredBuffer<int> gFreeListIndex : register(u3);


// �������Ԃ̍X�V��ratio�v�Z
void UpdateLifeTime(uint index)
{
    gLifeTime[index].current = max(gLifeTime[index].current - 1.0f, 0.0f);
    gLifeTime[index].ratio = saturate(1.0f - gLifeTime[index].current / gLifeTime[index].initTime);

    // �����I�����̏���
    if (gLifeTime[index].current <= 0.0f)
    {
        gParticles[index] = (ParticleCS) 0;
        gLifeTime[index] = (ParticleLifeTime) 0;
    }
}

// �p�[�e�B�N���̃��[���h���W�X�V
void UpdateParticleTransform(uint index)
{
    gParticles[index].translate += gParticles[index].velocity;
    gParticles[index].matWorld = AffineMatrix(
        gParticles[index].scale,
        gParticles[index].rotate,
        gParticles[index].translate
    );
}

// �t�F�[�h�A�E�g �� �v�Z
void UpdateFadeOutAlpha(uint index)
{
    float ratio = gLifeTime[index].ratio;
    gParticles[index].color.a = 1.0f - ratio;
}

// ���S�����p�[�e�B�N����FreeList�ɖ߂�
void RecycleDeadParticle(uint index)
{
    gParticles[index].scale = float3(0.0f, 0.0f, 0.0f);

    uint freeListIndex;
    InterlockedAdd(gFreeListIndex[0], 1, freeListIndex);

    if ((freeListIndex + 1) < kParticleInstanceMax)
    {
        gFreeList[freeListIndex + 1] = index;
    }
    else
    {
        // �͈͊O�ɂȂ����犪���߂�
        InterlockedAdd(gFreeListIndex[0], -1, freeListIndex);
    }
}


[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    uint index = DTid.x;

    if (index >= kParticleInstanceMax)
        return;

    if (gParticles[index].isAlive != 0)
    {
        if (gLifeTime[index].current <= 0.0f)
        {
            gParticles[index].isAlive = false;
        }

        UpdateLifeTime(index);
        UpdateParticleTransform(index);
        //UpdateFadeOutAlpha(index);
    }
    else
    {
        RecycleDeadParticle(index);
    }
}
