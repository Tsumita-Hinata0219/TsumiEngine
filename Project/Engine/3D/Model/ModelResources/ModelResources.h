#pragma once

#include "../../../BufferResource/BufferResource.h"
#include "../../../Transform/Transform.h"
#include "../ModelStructure/ModelStructure.h"


struct ModelDatas {

	// モデルの名前
	std::string name;

	// モデルファイルのフォーマット
	std::string fileFormat;

	// メッシュ
	MeshData mesh;

	// マテリアル
	MaterialDataN material{};

	// ライト
	DirectionalLightData light{};

	// 環境マップ
	EnvironmentData environment{};

	// ジョイントウェイト
	JointWeightData jointWeight{};

	// スケルトン
	Skeleton skeleton{};

	// スキンクラスター
	//SkinClusterData skinCluster{};
};

struct ModelBuffers {

	// メッシュ
	TsumiEngine::BufferResource<MeshData> mesh;

	// VertexDataBuffer
	TsumiEngine::BufferResource<VertexData> vertex;

	// IndexDataBuffer
	TsumiEngine::BufferResource<uint32_t> indeces;

	// マテリアル
	TsumiEngine::BufferResource<MaterialDataN> material;

	// Transform
	TsumiEngine::BufferResource<TransformationMat> transform;

	// ライト
	TsumiEngine::BufferResource<DirectionalLightData> light;

	// 環境マップ
	TsumiEngine::BufferResource<EnvironmentData> enviroment;

	// インフルエンス
	TsumiEngine::BufferResource<VertexInfluence> influence;

	// パレット
	TsumiEngine::BufferResource<WellForGPU> palette;
};