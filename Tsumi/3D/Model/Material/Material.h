#pragma once

#include "MyMath.h"
#include "Struct.h"

using namespace std;

struct MaterialDataN {
	Vector4 color;
	Matrix4x4 uvTransform;
};


/* Materialクラス */
struct Material {

public:

	// コンストラクタ、デストラクタ
	Material() {};
	~Material() {};

	// マテリアル作成
	void Create();

	// バッファ作成
	void CreateBuffer();

	// マッピングする
	void Map();

	// マッピング終了
	void UnMap();


public:

	// マテリアル名
	string name;

	// テクスチャハンドル
	uint32_t textureHandle = 1u;

	// カラー
	MaterialDataN materialData{};

	// 定数バッファ
	ComPtr<ID3D12Resource> constBuffer = nullptr;

	// マップアドレス
	MaterialDataN* constMap;
};

