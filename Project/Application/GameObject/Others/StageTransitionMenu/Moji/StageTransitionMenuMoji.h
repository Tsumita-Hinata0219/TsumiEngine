#pragma once

#include <list>
#include <memory>

#include "../../../IObject/IObject.h"
#include "../../../GameObject.h"


/* ステージ変更の文字 */
class StageTransitionMenuMoji {

public:

	/// <summary>
	/// コンストラクト
	/// </summary>
	StageTransitionMenuMoji() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StageTransitionMenuMoji() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init(const std::string& fileName);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw2DFront();


#pragma region Accessor アクセッサ

	// 座標
	Vector3 GetPosition() { return this->trans_.GetWorldPos(); }
	void SetPosition(const Vector3 setPos) { this->trans_.srt.translate = setPos; }

#pragma endregion 


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

