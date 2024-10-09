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
	BufferResource<SP::MeshData> mesh;

	// マテリアル
	BufferResource<SP::MaterialData> material;

	// Dissolve
	BufferResource<SP::DissolveData> dissolve;
};