#pragma once

#include "IObject/IObject.h"
#include "GameObject/GameObject.h"

#include "../Operation/StageSelectOperation.h"
#include "../Navigation/StageSelectNavigation.h"

#include <array>
#include <string>


/* ステージのセレクトクラス */
class StageSelectManager {

public:

	StageSelectManager() = default;
	~StageSelectManager() = default;

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

	// 選択したか
	bool IsSelect() const { return operation_->IsSelect(); }

	// 選んだステージ番号
	int GetSelectStageNum() const { return operation_->GetSelectNum(); }

#pragma endregion 


public:

	// ステージのMax数
	static const uint32_t kMaxStage = 5;


private:

	// 操作クラス
	std::unique_ptr<StageSelectOperation> operation_;

	// ナビゲーション
	std::unique_ptr<StageSelectNavigation> navigation_;
}; 
