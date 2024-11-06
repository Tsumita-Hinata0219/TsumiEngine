#include "GPUParticle.hlsli"

// ParticleÇÃóvëf
StructuredBuffer<ParticleCS> gParticles : register(t0);
// PreView
ConstantBuffer<PreView> gPreView : register(b0);


struct VertexShaderInput
{
    float4 position : POSITION0;
    float2 texcoord : TEXCOORD0;
    float4 color : COLOR0;
};


VertexShaderOutput main(VertexShaderInput input, uint instanceID : SV_InstanceID)
{
    VertexShaderOutput output;
    
    ParticleCS particle = gParticles[instanceID];
    float4x4 worldMatrix = gPreView.billboardMatrix; // worldMatrixÇçÏÇÈ
    worldMatrix[0] += particle.scale.x;
    worldMatrix[1] += particle.scale.y;
    worldMatrix[2] += particle.scale.z;
    worldMatrix[3].xyz += particle.translate;
    
    output.position = mul(input.position, mul(worldMatrix, gPreView.viewProjection));
    output.texcoord = input.texcoord;
    output.color = particle.color;    
    
    return output;
}