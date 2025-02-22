class RandomGenerator
{
    float3 seed3D;
    float2 seed2D;
    float4 seed4D;

    // 1D �����_���l�i0.0�`1.0�j
    float rand3dTo1d(float value, float3 dotDir = float3(12.9898, 78.233, 37.719))
    {
        float random = dot(value, dotDir);
        random = frac(sin(random) * 143758.5453);
        return random;
    }

    // 2D �� 2D �����i0.0�`1.0�j
    float2 rand2dTo2d(float2 value, float2 dotDir = float2(12.9898, 78.233))
    {
        float2 random = dot(value, dotDir);
        random = frac(sin(random) * 143758.5453);
        return random;
    }

    // 3D �� 3D �����i0.0�`1.0�j
    float3 rand3dTo3d(float3 value)
    {
        float3 result = float3(
            rand3dTo1d(value.x, float3(12.989, 78.233, 37.719)),
            rand3dTo1d(value.y, float3(39.346, 11.135, 83.155)),
            rand3dTo1d(value.z, float3(73.156, 52.235, 9.151))
        );
        seed3D = result;
        return result;
    }

    // 4D �� 4D �����i0.0�`1.0�j
    float4 rand4dTo4d(float4 value)
    {
        float4 result = float4(
            rand3dTo1d(value.x, float3(12.989, 78.233, 37.719)),
            rand3dTo1d(value.y, float3(39.346, 11.135, 83.155)),
            rand3dTo1d(value.z, float3(73.156, 52.235, 9.151)),
            rand3dTo1d(value.w, float3(31.279, 47.984, 61.387))
        );
        seed4D = result;
        return result;
    }

    // ���� 1D �����𐶐�
    float Generate1D()
    {
        seed3D.x = rand3dTo1d(seed3D.x);
        return seed3D.x;
    }

    // ���� 2D �����𐶐�
    float2 Generate2D()
    {
        seed2D = rand2dTo2d(seed2D);
        return seed2D;
    }

    // ���� 3D �����𐶐�
    float3 Generate3D()
    {
        seed3D = rand3dTo3d(seed3D);
        return seed3D;
    }

    // ���� 4D �����𐶐�
    float4 Generate4D()
    {
        seed4D = rand4dTo4d(seed4D);
        return seed4D;
    }

    // �w��͈� [minVal, maxVal] �̗�����Ԃ��i1D�j
    float RandomRange1D(float minVal, float maxVal)
    {
        return lerp(minVal, maxVal, Generate1D());
    }

    // �w��͈� [minVal, maxVal] �̗�����Ԃ��i2D�j
    float2 RandomRange2D(float2 minVal, float2 maxVal)
    {
        return lerp(minVal, maxVal, Generate2D());
    }

    // �w��͈� [minVal, maxVal] �̗�����Ԃ��i3D�j
    float3 RandomRange3D(float3 minVal, float3 maxVal)
    {
        return lerp(minVal, maxVal, Generate3D());
    }

    // �w��͈� [minVal, maxVal] �̗�����Ԃ��i4D�j
    float4 RandomRange4D(float4 minVal, float4 maxVal)
    {
        return lerp(minVal, maxVal, Generate4D());
    }
};
