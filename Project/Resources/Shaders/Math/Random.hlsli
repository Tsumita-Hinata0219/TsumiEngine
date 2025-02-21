class RandomGen
{
    float3 seed;

    // 3D��1D�̋^�����������i�͈�: 0�`1�j
    float rand3dTo1d(float value, float3 dotDir = float3(12.9898, 78.233, 37.719))
    {
        float random = dot(value, dotDir);
        random = frac(sin(random) * 143758.5453);
        return random;
    }

    // 3D��2D�̋^�����������i�͈�: 0�`1�j
    float2 rand3dTo2d(float2 value, float2 dotDir = float2(12.9898, 78.233))
    {
        float2 random = dot(value, dotDir);
        random = frac(sin(random) * 143758.5453);
        return random;
    }

    // 3D��3D�̋^�����������i�͈�: 0�`1�j
    float3 rand3dTo3d(float3 value)
    {
        float3 result = float3(
            rand3dTo1d(value.x, float3(12.989, 78.233, 37.719)),
            rand3dTo1d(value.y, float3(39.346, 11.135, 83.155)),
            rand3dTo1d(value.z, float3(73.156, 52.235, 9.151))
        );
        seed = result;
        return result;
    }

    // ����3D�����𐶐�
    float3 Generate3d()
    {
        seed = rand3dTo3d(seed);
        return seed;
    }

    // ����1D�����𐶐�
    float Generate1d()
    {
        seed.x = rand3dTo1d(seed.x);
        return seed.x;
    }

    // �w��͈� [minVal, maxVal] �̗�����Ԃ��i1D�j
    float RandomRange1D(float minVal, float maxVal)
    {
        return lerp(minVal, maxVal, Generate1d());
    }

    // �w��͈� [minVal, maxVal] �̗�����Ԃ��i3D�j
    float3 RandomRange3D(float3 minVal, float3 maxVal)
    {
        return lerp(minVal, maxVal, Generate3d());
    }
};
