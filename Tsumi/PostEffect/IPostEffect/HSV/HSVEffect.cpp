#include "HSVEffect.h"



// 初期化処理
void HSVEffect::Initialize()
{
	Create();

	// MtlData初期値
	mtlData_.color = Vector4::one;
	mtlData_.hue = 0.0f;
	mtlData_.saturation = 0.0f;
	mtlData_.value = 0.0f;
}


// 描画処理
void HSVEffect::Draw()
{
	// MtlBufferにMtlを書き込む
	mtlBuffer_.Map();
	mtlBuffer_.WriteData((&mtlData_));
	mtlBuffer_.UnMap();

	// コマンドコール
	CommandCall();
}


// ImGuiの描画
void HSVEffect::DrawImGui(std::string name)
{
#ifdef _DEBUG

	// Labelを追加する場合は追加
	label_ = label_ + name;

	if (ImGui::TreeNode((label_ + "HSV").c_str())) {

		ImGui::DragFloat("Hue", &mtlData_.hue, 0.01f, -1.0f, 1.0f);
		ImGui::DragFloat("Saturation", &mtlData_.saturation, 0.01f, -1.0f, 1.0f);
		ImGui::DragFloat("Value", &mtlData_.value, 0.01f, -1.0f, 1.0f);

		ImGui::TreePop();
	}

#endif // _DEBUG
}


// コマンドコール
void HSVEffect::CommandCall()
{
	// コマンドの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineの設定
	PipeLineManager::PipeLineCheckAndSet(PipeLineType::HSV);

	// SRVをコマンドに積む
	SRVManager::SetGraphicsRootDescriptorTable(3, srv_);

	// MtlBufferをコマンドに積む
	mtlBuffer_.CommandCall(4);

	// 描画
	commands.List->DrawInstanced(3, 1, 0, 0);
}
