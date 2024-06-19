#pragma once

#include "../../../Project/Math/MyMath.h"
#include "../../../Project/Math/Struct.h"
#include "../../CreateResource/CreateResource.h"

using namespace std;

enum class PostEffectType {
	None,
	GrayScale,
	Sepia,
	Vignetting,
	Smoothing,
	GaussianFilter,
	OutLine,
	RadialBlur,
	Dissolve,
	Random,
};

struct PostEffectMtlData {
	int type;
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

