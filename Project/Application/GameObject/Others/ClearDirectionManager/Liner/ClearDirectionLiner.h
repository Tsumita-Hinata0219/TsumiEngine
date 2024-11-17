#pragma once

#include <list>
#include <memory>

#include "../../../IObject/IObject.h"
#include "../../../GameObject.h"


/* クリア演出時の文字につくライナー */
class ClearDirectionLiner {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ClearDirectionLiner() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ClearDirectionLiner() = default;

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

