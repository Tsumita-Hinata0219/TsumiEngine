#include "HSVEffect.h"



// 初期化処理
void HSVEffect::Init()
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
	if (ImGui::TreeNode((name + "HSV").c_str())) {
		mtlData_.DrawImGui(name);
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
	//SRVManager::SetGraphicsRootDescriptorTable(3, srv_);
	renderTexBuffer_.GraphicsCommandCallSRV(3, srv_);

	// MtlBufferをコマンドに積む
	mtlBuffer_.GraphicsCommandCall(4);

	// 描画
	commands.List->DrawInstanced(3, 1, 0, 0);
}
