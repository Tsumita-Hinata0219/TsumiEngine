#include "RandomEffect.h"
#include "GameManager/GameManager.h"



// 初期化処理
void RandomEffect::Init()
{
	Create();

	// MtlData初期値
	mtlData_.color = Vector4::one;
}


// 描画処理
void RandomEffect::Draw()
{
	mtlData_.time = g_ElapsedTime;

	// MtlBufferにMtlを書き込む
	mtlBuffer_.Map();
	mtlBuffer_.WriteData((&mtlData_));
	mtlBuffer_.UnMap();

	// コマンドコール
	CommandCall();
}


// ImGuiの描画
void RandomEffect::DrawImGui(std::string name)
{
#ifdef _DEBUG
	if (ImGui::TreeNode((name + "Random").c_str())) {
		mtlData_.DrawImGui(name);
		ImGui::TreePop();
	}
#endif // _DEBUG
}


// コマンドコール
void RandomEffect::CommandCall()
{
	// コマンドの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineの設定
	PipeLineManager::PipeLineCheckAndSet(PipeLineType::Random);

	// SRVをコマンドに積む
	SRVManager::SetGraphicsRootDescriptorTable(3, srv_);

	// MtlBufferをコマンドに積む
	mtlBuffer_.CommandCall(4);

	// 描画
	commands.List->DrawInstanced(3, 1, 0, 0);
}