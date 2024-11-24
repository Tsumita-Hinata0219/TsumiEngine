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
	MeshData mesh{};

	// マテリアル
	MaterialDataN material{};

	// フリーカウンター
	uint32_t freeCounter = 0;

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

	// FreeCounter
	BufferResource<uint32_t> freeCounter;

	// PreView
	BufferResource<GPUParticlePreView> preView;

	// Transform
	BufferResource<TransformationMat> transform;

	// マテリアル
	BufferResource<MaterialDataN> material;

	// ライト
	//BufferResource<DirectionalLightData> light;
};

