#include "../GPUParticle.hlsli"


// Particleの要素
StructuredBuffer<ParticleCS> gParticles : register(t0);
// PreView
ConstantBuffer<PreView> gPreView : register(b0);

// Main
VertexShaderOutput main(VertexShaderInput input, uint instanceID : SV_InstanceID)
{
    VertexShaderOutput output;
    
    ParticleCS particle = gParticles[instanceID];
    float4x4 worldMatrix = gPreView.billboardMatrix; // worldMatrixを作る
    worldMatrix[0] += particle.scale.x;
    worldMatrix[1] += particle.scale.y;
    worldMatrix[2] += particle.scale.z;
    worldMatrix[3].xyz += particle.translate;
    
    // 頂点の位置をワールド・ビュー・プロジェクション行列で変換
    output.position = mul(input.position, mul(worldMatrix, gPreView.viewProjection));
    
    // テクスチャ座標はそのまま渡す
    output.texcoord = input.texcoord;
    
    // InstanceIDはそのまま渡す
    output.instanceID = instanceID;
    
    return output;
}
