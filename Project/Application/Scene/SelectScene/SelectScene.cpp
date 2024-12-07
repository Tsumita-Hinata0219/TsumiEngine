#include "SelectScene.h"



/// <summary>
/// 初期化処理
/// </summary>
void SelectScene::Initialize()
{
	// セレクト
	selectManager_ = StageSelectManager::GetInstrance();
	selectManager_->Init();
}


/// <summary>
/// 更新処理
/// </summary>
void SelectScene::Update(GameManager* state)
{
	state;

	// セレクト
	selectManager_->Update();


#ifdef _DEBUG
	ImGui::Begin("ResultScene");
	ImGui::End();
#endif // _DEBUG
}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void SelectScene::BackSpriteDraw()
{
}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void SelectScene::ModelDraw()
{
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void SelectScene::FrontSpriteDraw()
{
}
