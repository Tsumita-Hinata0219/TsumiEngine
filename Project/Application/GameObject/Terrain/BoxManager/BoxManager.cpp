#include "BoxManager.h"



/// <summary>
/// 初期化処理
/// </summary>
void BoxManager::Init()
{
}


/// <summary>
/// 更新処理
/// </summary>
void BoxManager::Update()
{
	// BoxListの更新処理
	for (std::shared_ptr<IBoxObject> box : boxs_) {
		box->Update();
	}
}


/// <summary>
/// 描画処理
/// </summary>
void BoxManager::Draw3D()
{
	for (std::shared_ptr<IBoxObject> box : boxs_) {
		box->Draw3D();
	}
}


/// <summary>
/// Jsonで読み込んだ情報を受け取る
/// </summary>
void BoxManager::LoadEntityData(const std::vector<std::unique_ptr<EntityData>>& datas)
{
	datas;
}


/// <summary>
/// 新しいボックスを作る
/// </summary>
void BoxManager::CreateNewBox(BoxType type, const SRTN& setSRT)
{
	type, setSRT;
}
