#pragma once

#include "MyMath.h"
#include "Struct.h"
#include "CreateResource.h"

using namespace std;

struct PostEffectMtlData {
	Vector4 color;
};

/* PostEffectMaterial構造体 */
struct PostEffectMaterial {

	// コンストラクタ
	PostEffectMaterial() = default;


	// マテリアル作成
	void Create();

	// マテリアルの転送
	void TransferMaterial();


	// 定数バッファ構造体
	PostEffectMtlData mtlData{};

	// 定数バッファ
	ComPtr<ID3D12Resource> constBuffer = nullptr;

	// マップアドレス
	PostEffectMtlData* constMap{};


private:

	// バッファ作成
	void CreateBuffer();

	// マッピングする
	void Map();

	// マッピング終了
	void UnMap();
};

