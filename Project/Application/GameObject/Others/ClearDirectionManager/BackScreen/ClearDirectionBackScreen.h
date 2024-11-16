#pragma once

#include <list>
#include <memory>

#include "../../../IObject/IObject.h"
#include "../../../GameObject.h"


/* GameScene内のUI */
class ClearDirectionBackScreen {

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
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw2DFront();

private:

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawImGui();


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

