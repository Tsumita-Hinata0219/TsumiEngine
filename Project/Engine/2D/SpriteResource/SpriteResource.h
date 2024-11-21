#pragma once

#include "BufferResource/BufferResource.h"
#include "Transform/Transform.h"
#include "../Structure/SpriteStructure.h"

struct SpriteDatas {

	// メッシュ
	SP::MeshData mesh{};

	// マテリアル
	SP::MaterialData material{};

	// Dissolve
	SP::DissolveData dissolve{};
};

struct SpriteBuffers {

	// メッシュ
	TsumiEngine::BufferResource<SP::MeshData> mesh;

	// VertexDataBuffer
	TsumiEngine::BufferResource<VertexData> vertex;

	// IndexDataBuffer
	TsumiEngine::BufferResource<uint32_t> indeces;

	// マテリアル
	TsumiEngine::BufferResource<SP::MaterialData> material;

	// Dissolve
	TsumiEngine::BufferResource<SP::DissolveData> dissolve;

	// Transform
	TsumiEngine::BufferResource<TransformationMat> transform;
};