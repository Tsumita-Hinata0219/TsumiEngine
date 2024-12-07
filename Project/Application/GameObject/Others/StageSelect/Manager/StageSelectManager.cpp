#include "StageSelectManager.h"



/// <summary>
/// インスタンス取得
/// </summary>
StageSelectManager* StageSelectManager::GetInstrance()
{
	static StageSelectManager instance;
	return &instance;
}


/// <summary>
/// 初期化処理
/// </summary>
void StageSelectManager::Init()
{
	// 一度通っていれば早期return
	if (isVisited_) { return; }

	// ファイルパスの設定
	stageJsonFilePaths_ = {
		"Stage_Demo.json",
		"Stage_1.json",
		"Stage_2.json",
		"Stage_3.json",
		"Stage_4.json",
		"Stage_5.json",
	};

	// セレクトしたステージのファイルパス
	selectStageFP_ = stageJsonFilePaths_[0];

	// 操作クラス
	operation_ = std::make_unique<StageSelectOperation>();
	operation_->Init();

	// 一度通った
	isVisited_ = true;
}


/// <summary>
/// 更新処理
/// </summary>
void StageSelectManager::Update()
{
	// 操作クラス
	operation_->Update();




}

