#pragma once

#include <list>
#include <memory>

#include "../../../IObject/IObject.h"
#include "../../../GameObject.h"
#include "../IClearDirection.h"


/* クリア演出時のバックスクリーン */
class ClearDirectionBackScreen : public IClearDirection {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ClearDirectionBackScreen() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ClearDirectionBackScreen() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw2DFront() override;

private:

	/// <summary>
	/// 演出開始
	/// </summary>
	void StartDirection() override;

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawImGui() override;


private:

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// スプライト
	std::unique_ptr<Sprite> sprite_;

	// トランスフォーム
	Transform trans_{};

	// カラー
	Vector4 color_{};

};

