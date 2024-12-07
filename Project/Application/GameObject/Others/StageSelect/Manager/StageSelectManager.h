#pragma once

#include "GameObject/IObject/IObject.h"
#include "GameObject/GameObject.h"

#include "../Operation/StageSelectOperation.h"

#include <array>
#include <string>


/* ステージのセレクトクラス */
class StageSelectManager {

private: // シングルトン

	StageSelectManager() = default;
	~StageSelectManager() = default;
	StageSelectManager(const StageSelectManager&) = delete;
	const StageSelectManager& operator=(const StageSelectManager&) = delete;

public:

	/// <summary>
	/// インスタンス取得
	/// </summary>
	static StageSelectManager* GetInstrance();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


#pragma region Accessor アクセッサ

#pragma endregion 


public:

	// ステージのMax数
	static const uint32_t kMaxStage = 10;

	// セレクトしたステージのファイルパス(FP)
	std::string selectStageFP_{};


private:

	// 一度通ったかのフラグ
	bool isVisited_ = false;

	// Jsonファイルパスの配列
	std::array<std::string, kMaxStage> stageJsonFilePaths_;

	// 操作クラス
	std::unique_ptr<StageSelectOperation> operation_;
}; 
