#pragma once

#include "MyMath.h"
#include "Struct.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "TextureManager.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "SpriteGraphicPipeline.h"
#include "CreateResource.h"
#include "DescriptorManager.h"


struct SpriteTransform {
	Vector2 scale{};
	Vector2 rotate{};
	Vector2 translate{};
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
	void Initialize(Vector2 pos, Vector2 size);


	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(uint32_t texHandle, WorldTransform& transform, ViewProjection view);

	/// <summary>
	/// 色の変換
	/// </summary>
	Vector4 FloatColor(unsigned int color);


#pragma region Set 設定

	void SetWorldTransform(WorldTransform worldTransform) { worldTansform_ = worldTansform_; }
	void SetUVTransform(UVTransform uvTransform) { uvTransform_ = uvTransform; }
	void SetPosition(Vector2 position) { pos_ = position; }
	void SetTextureHandle(uint32_t texHD) { useTexture_ = texHD; }
	void SetSize(Vector2 size) { size_ = size; }
	void SetColor(Vector4 color) { color_ = color; }

#pragma endregion


private:

	/// <summary>
	/// 頂点データを設定する
	/// </summary>
	void SetVertex(WorldTransform transform);


private:

	// ワールドトランスフォーム
	WorldTransform worldTansform_;
	SpriteTransform spriteTransform_{};

	// 座標
	Vector2 pos_;

	// 画像サイズ
	Vector2 size_;

	// テクスチャ
	uint32_t useTexture_;

	// 色データ
	Vector4 color_;

	// リソース
	ResourcePeroperty resource_{};

	// uvTransform 
	UVTransform uvTransform_;
};


