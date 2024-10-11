#pragma once

#include "Base/WinApp/WinApp.h"
#include "Base/DXCommon/DirectXCommon.h"
#include "Transform/WorldTransform/WorldTransform.h"
#include "TextureManager/TextureManager.h"
#include "PipeLineManager/PipeLineManager.h"
#include "CreateResource/CreateResource.h"
#include "DescriptorManager/DescriptorManager.h"
#include "View/SRVManager/SRVManager.h"
#include "GameObject/Camera/Manager/CameraManager.h"
#include "Math/MyMath.h"
#include "Math/Struct.h"

#include "../SpriteResource/SpriteResource.h"



// CameraManagerの前方宣言
class CameraManager;

enum class SpriteAnchor {
	TopLeft,
	Center,
};



class Sprite {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Sprite() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Sprite() {};


	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init(Vector2 size = { 128.0f, 128.0f }, Vector4 color = Vector4::one);
	void Initn(Vector2 size = { 128.0f, 128.0f });


	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(uint32_t texHandle, WorldTransform& transform);
	void Draw(uint32_t texHandle, Transform& transform);

	/// <summary>
	/// 色の変換
	/// </summary>
	Vector4 FloatColor(unsigned int color);


#pragma region Set 設定

	void SetSize(Vector2 size) { size_ = size; }
	void SetUVTransform(UVTransform uvTransform) { uvTransform_ = uvTransform; }
	void SetTextureHandle(uint32_t texHD) { useTexture_ = texHD; }
	void SetColor(Vector4 color) { color_ = color; }
	void SetSrc(QuadVertex2 src) { src_ = src; }
	void SetAnchor(SpriteAnchor setOrigin) { anchor_ = setOrigin; }

#pragma endregion


private:

	// コマンドコール
	void CommandCall();

	// DatasをもとにBufferを作成
	void CreateBufferResource();

	// メッシュデータの設定
	void SetMeshData();

	// 頂点データを設定する
	void SetVertex(WorldTransform transform);


private:

	// スプライトトランスフォーム
	WorldTransform worldTransform_{};

	// サイズ
	Vector2 size_{};

	// テクスチャ
	uint32_t useTexture_ = 0;

	// 色データ
	Vector4 color_;

	// リソース
	ResourcePeroperty resource_{};

	// uvTransform 
	UVTransform uvTransform_;

	// SRC
	QuadVertex2 src_ = {
		{0.0f, 0.0f},
		{0.0f, 1.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
	};

	uint32_t srv_ = 0;


	// バッファーに書き込むデータ
	SpriteDatas datas_{};

	// バッファー
	SpriteBuffers buffers_{};

	// カメラマネージャー
	CameraManager* cameraManager_ = nullptr;

	// スプライトの基準
	SpriteAnchor anchor_ = SpriteAnchor::TopLeft;

	// VerticesとIndicesのサイズ
	const uint32_t verticesSize_ = 4;
	const uint32_t indicesSize_ = 6;
};



// UIの描画に必要なもの
struct SpriteProperty {
	std::unique_ptr<Sprite> sprite;
	WorldTransform transfrom;
	uint32_t texture = 0;
};
