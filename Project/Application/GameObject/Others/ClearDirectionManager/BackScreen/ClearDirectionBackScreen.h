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
	void DirectionStart() override;

	/// <summary>
	/// 演出更新
	/// </summary>
	void DirectionUpdate() override;

	/// <summary>
	/// 演出終了
	/// </summary>
	void DirectionExsit() override;

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

	// タイマー
	Timer timer_{};

	// Alpha値の初期値、目標値
	float initAlpha_ = 0.0f;
	float targetAlpha_ = 1.0f;
};

