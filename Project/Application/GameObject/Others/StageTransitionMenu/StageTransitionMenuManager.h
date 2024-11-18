#pragma once

#include "GameObject/GameObject.h"
#include "Math/MyMath.h"

#include "IStageTransitionMenu.h"
#include "BackScreen/StageTransitionMenuBackScreen.h"
#include "Blur/StageTransitionMenuBlur.h"
#include "Navigation/StageTransitionMenuNavigation.h"
#include "ResultUI/StageTransitionMenuResultUI.h"
#include "TextLine/StageTransitionMenuTextLine.h"


enum class STMenuType {
	BackScreen,
	Blur,
	Navigation_Back,
	Navigation_Next,
	ResultUI,
	TextLine,
	Count,
};


/* ステージ変更メニュー */
class StageTransitionMenuManager {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	StageTransitionMenuManager() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StageTransitionMenuManager() = default;

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
	MenuDirectionState GetState() const { return this->state_; }



private:

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawImGui();

	/// <summary>
	/// Stateの描画
	/// </summary>
	void ShowState(const char* label, MenuDirectionState state);
	

private:

	Input* input_ = nullptr;

	// Menu
	std::vector<std::unique_ptr<IStageTransitionMenu>> menus_;

	// State
	MenuDirectionState state_;

	// 演出をするかのフラグ
	bool isActive_ = false;

};

