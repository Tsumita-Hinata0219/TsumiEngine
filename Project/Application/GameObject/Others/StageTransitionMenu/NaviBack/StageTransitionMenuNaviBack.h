#pragma once

#include <list>
#include <memory>

#include "../../../IObject/IObject.h"
#include "../../../GameObject.h"
#include "../IStageTransitionMenu.h"
#include "PostEffect/IPostEffect/RadialBlur/RadialBlurEffect.h"


/* ゲーム終了メニューのナビゲーションバック */
class StageTransitionMenuNaviBack {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	StageTransitionMenuNaviBack() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StageTransitionMenuNaviBack() = default;

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
	uint32_t backTexHD_ = 0;
	uint32_t frameTexHD_ = 0;

	// スプライト
	std::unique_ptr<Sprite> back_;
	std::unique_ptr<Sprite> frame_;

	// トランスフォーム
	Transform backTrans_{};
	Transform frameTrans_{};

	// カラー
	Vector4 color_{};

};

