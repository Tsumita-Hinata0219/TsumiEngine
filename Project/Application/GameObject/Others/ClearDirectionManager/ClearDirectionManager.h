#pragma once

#include "GameObject/GameObject.h"
#include "Math/MyMath.h"

#include "IClearDirection.h"
#include "Blur/ClearDirectionBlur.h"
#include "BackScreen/ClearDirectionBackScreen.h"
#include "Liner/ClearDirectionLiner.h"
#include "Moji/ClearDirectionMoji.h"


/* クリア演出のクラス */
class ClearDirectionManager {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ClearDirectionManager() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ClearDirectionManager() = default;

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

	/// <summary>
	/// 演出開始
	/// </summary>
	void DirectionStart();

	/// <summary>
	/// ステートの取得
	/// </summary>
	ClearDirectionState GetState() const { return this->state_; }


private:

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawImGui();

	/// <summary>
	/// Stateの描画
	/// </summary>
	void ShowState(const char* label, ClearDirectionState state);


private:

	Input* input_ = nullptr;

	// ClearDirections
	std::vector<std::unique_ptr<IClearDirection>> directions_;

	// State
	ClearDirectionState state_;

	// 演出をするかのフラグ
	bool isActive_ = false;

};

