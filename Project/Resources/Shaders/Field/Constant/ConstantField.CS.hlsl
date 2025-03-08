#include "../Field.hlsli"
#include "../../Math/Math.hlsli"
#include "../../Random/Random.hlsli"


// パーティクル最大インスタンス数
static const uint kParticleInstanceMax = 1024;


[numthreads(1024, 1, 1)]
void main(int3 DTid : SV_DispatchThreadID)
{
    
}