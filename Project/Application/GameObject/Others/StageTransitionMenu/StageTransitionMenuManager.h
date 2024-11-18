#pragma once

#include "GameObject/GameObject.h"
#include "Math/MyMath.h"


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


private:

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawImGui();
	
private:




};

