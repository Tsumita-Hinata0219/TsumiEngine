#pragma once

#include "../../../BufferResource/BufferResource.h"
#include "../../../Transform/Transform.h"
#include "../Structure/ModelStructure.h"


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

	// 色加算
	ColorAddition colorAddition{};

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
	BufferResource<uint32_t> indices;

	// マテリアル
	BufferResource<MaterialDataN> material;

	// Transform
	BufferResource<TransformationMat> transform;

	// ライト
	BufferResource<DirectionalLightData> light;

	// 環境マップ
	BufferResource<EnvironmentData> enviroment;

	// 色加算
	BufferResource<ColorAddition> colorAddition;

	// インフルエンス
	BufferResource<VertexInfluence> influence;

	// パレット
	BufferResource<WellForGPU> palette;
};