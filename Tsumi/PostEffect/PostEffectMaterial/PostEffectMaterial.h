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


/* BasePostEffectMaterial構造体 */
struct PostEffectMtlData {
	Vector4 color;
	Matrix4x4 projectionInverse;
};
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



/* VignettingMaterial構造体 */
struct VignettingMtlData {

	Vector4 color;
	Vector2 center; // ビネットの中心位置
	float intensity; // ビネットの強さ
	float smoothness; // スムーズさ
	float roundness; // 丸みの設定
	bool rounded; // ビネットの形状設定 (丸いビネットを使用するか)
};
struct VignettingMaterial {

	// コンストラクタ
	VignettingMaterial() = default;

	// マテリアル作成
	void Create();

	// マテリアルの転送
	void TransferMaterial();


	// 定数バッファ構造体
	VignettingMtlData mtlData{};

	// 定数バッファ
	ComPtr<ID3D12Resource> constBuffer = nullptr;

	// マップアドレス
	VignettingMtlData* constMap{};


private:

	// バッファ作成
	void CreateBuffer();

	// マッピングする
	void Map();

	// マッピング終了
	void UnMap();
};



/* ColorGradingMaterial構造体 */
struct ColorGradingMtlData {
	Vector4 color;
	Vector3 tone;
	float contrast;
	float saturation;
	float brightness;
	float hueShift;
	float temperature;
	float tint;
	float postExposure;
	Vector4 colorFilter;
	float gamma;
};
struct ColorGradingMaterial {

	// コンストラクタ
	ColorGradingMaterial() = default;

	// マテリアル作成
	void Create();

	// マテリアルの転送
	void TransferMaterial();


	// 定数バッファ構造体
	PostEffectMtlData mtlData{};

	// 定数バッファ
	ComPtr<ID3D12Resource> constBuffer = nullptr;

	// マップアドレス
	VignettingMtlData* constMap{};


private:

	// バッファ作成
	void CreateBuffer();

	// マッピングする
	void Map();

	// マッピング終了
	void UnMap();
};
