#include "RadialBlurEffect.h"



// 初期化処理
void RadialBlurEffect::Init()
{
	Create();

	// MtlData初期値
	mtlData_.color = Vector4::one;
}


// 描画処理
void RadialBlurEffect::Draw()
{
	// MtlBufferにMtlを書き込む
	mtlBuffer_.Map();
	mtlBuffer_.WriteData((&mtlData_));
	mtlBuffer_.UnMap();

	// コマンドコール
	CommandCall();
}


// ImGuiの描画
void RadialBlurEffect::DrawImGui(std::string name)
{
#ifdef _DEBUG
	if (ImGui::TreeNode((name + "RadialBlur").c_str())) {
		mtlData_.DrawImGui(name);
		ImGui::TreePop();
	}
#endif // _DEBUG
}


// コマンドコール
void RadialBlurEffect::CommandCall()
{
	// コマンドの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineの設定
	PipeLineManager::SetPipeLine(PipeLine::Container::Graphic, PipeLine::Category::RadialBlur);


	// SRVをコマンドに積む
	//SRVManager::SetGraphicsRootDescriptorTable(3, srv_);
	renderTexBuffer_.GraphicsCommandCallSRV(3, srv_);

	// MtlBufferをコマンドに積む
	mtlBuffer_.GraphicsCommandCall(4);

	// 描画
	commands.List->DrawInstanced(3, 1, 0, 0);
}
