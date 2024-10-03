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
	BufferResource<MeshData> mesh;

	// VertexDataBuffer
	BufferResource<VertexData> vertex;

	// IndexDataBuffer
	BufferResource<uint32_t> indeces;

	// マテリアル
	BufferResource<MaterialDataN> material;

	// WorldTransform
	BufferResource<TransformationMat> transform;

	// ライト
	BufferResource<DirectionalLightData> light;

	// 環境マップ
	BufferResource<EnvironmentData> enviroment;

	// インフルエンス
	BufferResource<VertexInfluence> influence;

	// パレット
	BufferResource<WellForGPU> palette;
};