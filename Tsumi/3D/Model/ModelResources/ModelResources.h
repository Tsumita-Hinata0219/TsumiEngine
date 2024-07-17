#pragma once

#include "../../../BufferResource/BufferResource.h"
#include "../../../Transform/Transform.h"
#include "../ModelStructure/Mesh/Mesh.h"
#include "../ModelStructure/Material/Material.h"


/* ModelResource構造体 */
struct ModelResources {

	// ModelName
	std::string name_;

	// FileFormat
	std::string fileFormat_;

	// Mesh
	MeshData meshData_;
	BufferResource<MeshData> meshBuffer_;

	// VertexDataBuffer
	BufferResource<VertexData> vertexBuffer_;

	// IndexDataBuffer
	BufferResource<uint32_t> indecesBuffer_;

	// Materil
	MaterialDataN materialData_;
	BufferResource<MaterialDataN> materialBuffer_;

	// WorldTransform
	BufferResource<TransformationMat> transformBuffer_;

	// DirectionLight
	DirectionalLightData lightData_;
	BufferResource<DirectionalLightData> lightBuffer_;
};

