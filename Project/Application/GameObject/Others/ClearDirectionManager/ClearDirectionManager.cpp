#include "ClearDirectionManager.h"



/// <summary>
/// 初期化処理
/// </summary>
void ClearDirectionManager::Init()
{
	/* ----- Direction 演出 ----- */
	directions_.resize(3);
	directions_[0] = std::make_unique<ClearDirectionBackScreen>();
	directions_[1] = std::make_unique<ClearDirectionLiner>();
	directions_[2] = std::make_unique<ClearDirectionMoji>();
	// 各演出の初期化
	for (auto& element : directions_) {
		element->Init();
	}
}


/// <summary>
/// 更新処理
/// </summary>
void ClearDirectionManager::Update()
{
	// 各演出の更新
	for (auto& element : directions_) {
		element->Update();
	}
}


/// <summary>
/// 描画処理
/// </summary>
void ClearDirectionManager::Draw2DFront()
{
	// 各演出の描画
	for (auto& element : directions_) {
		element->Draw2DFront();
	}

}

