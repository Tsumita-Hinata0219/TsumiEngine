#include "DissolveEffect.h"



// 初期化処理
void DissolveEffect::Init()
{
	Create();

	mtlData_.maskTexture = TextureManager::LoadTexture("Texture", "noise0.png");
}


// 描画処理
void DissolveEffect::Draw()
{
	// MtlBufferにMtlを書き込む
	mtlBuffer_.Map();
	mtlBuffer_.WriteData(&mtlData_);
	mtlBuffer_.UnMap();

	// コマンドコール
	CommandCall();
}


// ImGuiの描画
void DissolveEffect::DrawImGui(std::string name)
{
#ifdef _DEBUG	
	if (ImGui::TreeNode((name + "Dissolve").c_str())) {
		mtlData_.DrawImGui(name);
		ImGui::TreePop();
	}
#endif // _DEBUG
}


// コマンドコール
void DissolveEffect::CommandCall()
{
	// コマンドの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineの設定
	PipeLineManager::PipeLineCheckAndSet(PipeLineType::Dissolve);

	// SRVをコマンドに積む
	SRVManager::SetGraphicsRootDescriptorTable(3, srv_);

	// MtlBufferをコマンドに積む
	mtlBuffer_.CommandCall(4);

	// MaksTexture
	SRVManager::SetGraphicsRootDescriptorTable(5, mtlData_.maskTexture);

	// 描画
	commands.List->DrawInstanced(3, 1, 0, 0);
}
