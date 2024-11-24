#pragma once

#include "../../BufferResource/BufferResource.h"
#include "../../Transform/Transform.h"
#include "../../3D/Model/ModelStructure/ModelStructure.h"
#include "../Structure/GPUParticleStructure.h"


struct ParticleData {
	Matrix4x4 world;
	Vector4 color;
};


struct GPUParticleDatas {
	
	// モデルの名前
	std::string name;

	// メッシュ
	MeshData mesh;

	// マテリアル
	MaterialDataN material{};

	// ライト
	//DirectionalLightData light{};
};

struct GPUParticleResources {

	// メッシュ
	BufferResource<MeshData> mesh;

	// VertexDataBuffer
	BufferResource<VertexData> vertex;

	// IndexDataBuffer
	BufferResource<uint32_t> indeces;

	// ParticleElement
	BufferResource<GPUParticleCS> particleElement;

	// PreView
	BufferResource<GPUParticlePreView> preView;

	// Transform
	BufferResource<TransformationMat> transform;

	// マテリアル
	BufferResource<MaterialDataN> material;

	// ライト
	//BufferResource<DirectionalLightData> light;
};

