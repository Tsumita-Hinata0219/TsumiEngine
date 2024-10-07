#include "TitleLabelObject.h"



// パラメータ付きコンストラクタ
TitleLabelObject::TitleLabelObject(std::pair<std::string, std::string> file)
{
	this->file_ = file;
}


// 初期化処理
void TitleLabelObject::Init()
{
	// Modelの設定
	modelManager_ = ModelManager::GetInstance();
	modelManager_->LoadModel(file_.first, file_.second);
	model_ = modelManager_->GetModel(RemoveExtension(file_.second)); // ファイル名だけを抽出

	// 初期カラーは黒
	model_->SetColor(Samp::Color::BLACK);

	// Transformの初期化
	trans_.Init();
}


// 更新処理
void TitleLabelObject::Update() 
{

#ifdef _DEBUG

	if (ImGui::TreeNode("TitleLabel")) {

		trans_.DrawImGui(RemoveExtension(file_.second));
		ImGui::TreePop();
	}

#endif // _DEBUG
}


// 描画処理
void TitleLabelObject::Draw3D()
{
	model_->DrawN(trans_);
}
void TitleLabelObject::Draw2DFront() {}
void TitleLabelObject::Draw2DBack() {}


// 衝突判定コールバック関数
void TitleLabelObject::onCollision([[maybe_unused]] IObject* object)
{
}
