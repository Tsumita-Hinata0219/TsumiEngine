
float4x4 Mat4x4Identity()
{
    return float4x4(
          float4(1.0f, 0.0f, 0.0f, 0.0f),
          float4(0.0f, 1.0f, 0.0f, 0.0f),
          float4(0.0f, 0.0f, 1.0f, 0.0f),
          float4(0.0f, 0.0f, 0.0f, 1.0f)
    );
}

float4x4 ScaleMatrix(float3 scale)
{
    return float4x4(
        scale.x, 0.0, 0.0, 0.0,
        0.0, scale.y, 0.0, 0.0,
        0.0, 0.0, scale.z, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

float4x4 TranslateMatrix(float3 translation)
{
    return
    float4x4(
        1.0, 0.0, 0.0, 0.0f,
        0.0, 1.0, 0.0, 0.0f,
        0.0, 0.0, 1.0, 0.0f,
        translation.x, translation.y, translation.z, 1.0
    );
}

float4x4 RotateMatrixX(float angle)
{
    float s = sin(angle);
    float c = cos(angle);
    return float4x4(
        1.0, 0.0, 0.0, 0.0,
        0.0, c, -s, 0.0,
        0.0, s, c, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

float4x4 RotateMatrixY(float angle)
{
    float s = sin(angle);
    float c = cos(angle);
    return float4x4(
        c, 0.0, s, 0.0,
        0.0, 1.0, 0.0, 0.0,
        -s, 0.0, c, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

float4x4 RotateMatrixZ(float angle)
{
    float s = sin(angle);
    float c = cos(angle);
    return float4x4(
        c, -s, 0.0, 0.0,
        s, c, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

float4x4 AffineMatrix(float3 scale, float3 rotate, float3 translate)
{
    float4x4 scalingMatrix = ScaleMatrix(scale);
    float4x4 rotationMatrixX = RotateMatrixX(rotate.x);
    float4x4 rotationMatrixY = RotateMatrixY(rotate.y);
    float4x4 rotationMatrixZ = RotateMatrixZ(rotate.z);
    float4x4 translationMatrix = TranslateMatrix(translate);
    float4x4 rotateXYZ = Mat4x4Identity();
    rotateXYZ = mul(rotateXYZ, mul(rotationMatrixX, mul(rotationMatrixY, rotationMatrixZ)));
    return mul(scalingMatrix, mul(rotateXYZ, translationMatrix));

}

//float32_3x3 InverseTranspose(float32_3x3 input)
//{
//    float32_3x3 result = input;
    
//    for (int i = 0; i < 3; i++)
//    {
//        result[i] /= length(result[i]);
//    }
    
//    return result;
//}
