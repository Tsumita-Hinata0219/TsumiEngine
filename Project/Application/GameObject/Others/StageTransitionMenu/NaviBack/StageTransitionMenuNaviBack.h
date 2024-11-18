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


#pragma region Accessor アクセッサ
	
	// ターゲット座標
	void SetTargetPos(Vector3 setA, Vector3 setB) { targetPos_ = { setA, setB }; }

#pragma endregion 


private:

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawImGui();


private:

	// 配列サイズ
	static const uint32_t arraySize_ = 2;

	// テクスチャハンドル
	std::array<uint32_t, arraySize_> texHDArr_;

	// スプライト
	std::array<std::unique_ptr<Sprite>, arraySize_> spriteArr_;

	// スプライトサイズ
	std::array<Vector2, arraySize_> sizeArr_;

	// トランスフォーム
	std::array<Transform, arraySize_> transArr_;

	// ターゲット座標
	std::array<Vector3, arraySize_> targetPos_;

};

