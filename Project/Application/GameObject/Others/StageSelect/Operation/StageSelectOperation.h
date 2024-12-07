#pragma once

#include "GameObject/IObject/IObject.h"
#include "GameObject/GameObject.h"


/* ステージセレクトの操作クラス */
class StageSelectOperation {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	StageSelectOperation() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StageSelectOperation() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

private:

	/// <summary>
	/// セレクトの操作
	/// </summary>
	void SelectOperation();

	/// <summary>
	/// DrawImGuiの描画
	/// </summary>
	void DrawImGui();


private:

	// Inputクラス
	Input* input_ = nullptr;

	// ステージのセレクト番号
	int selectNum_ = 0;

};

