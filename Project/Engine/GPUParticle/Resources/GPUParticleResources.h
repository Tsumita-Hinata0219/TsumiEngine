#pragma once

#include "../../BufferResource/BufferResource.h"
#include "../../Transform/Transform.h"
#include "../../3D/Model/ModelStructure/ModelStructure.h"


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

	// マテリアル
	BufferResource<MaterialDataN> material;

	// Transform
	BufferResource<TransformationMat> transform;

	// ライト
	//BufferResource<DirectionalLightData> light;
};

