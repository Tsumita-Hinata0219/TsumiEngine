#pragma once

#include "../../BufferResource/BufferResource.h"
#include "../../Transform/Transform.h"
#include "../../3D/Model/Structure/ModelStructure.h"
#include "../Structure/ParticleStructure.h"



namespace GpuParticle {

struct InstanceProperties {
	Matrix4x4 world;
	Vector4 color;
};


struct ModelData {

	// モデルの名前
	std::string name;

	// メッシュ
	MeshData mesh;

	// マテリアル
	MaterialDataN material{};

	// ライト
	//DirectionalLightData light{};
};

struct ResourceHandles {

	// メッシュ
	BufferResource<MeshData> mesh;

	// VertexDataBuffer
	BufferResource<VertexData> vertex;

	// IndexDataBuffer
	BufferResource<uint32_t> indeces;

	// ParticleElement
	BufferResource<GpuParticle::PropertyCS> particleElement;

	// PreView
	BufferResource<GpuParticle::PreView> preView;

	// Transform
	BufferResource<TransformationMat> transform;

	// マテリアル
	BufferResource<MaterialDataN> material;

	// ライト
	//BufferResource<DirectionalLightData> light;
};
}

