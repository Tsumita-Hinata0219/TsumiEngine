#include "AbsentEffect.h"



// 初期化処理
void AbsentEffect::Init()
{
	Create();

}


// 描画処理
void AbsentEffect::Draw()
{
	// コマンドコール
	CommandCall();
}


// ImGuiの描画
void AbsentEffect::DrawImGui(std::string name)
{
#ifdef _DEBUG
	if (ImGui::TreeNode((name + "Absent").c_str())) {
		ImGui::TreePop();
	}
#endif // _DEBUG
}


// コマンドコール
void AbsentEffect::CommandCall()
{
	// コマンドの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineの設定
	PipeLineManager::PipeLineCheckAndSet(PipeLineType::Absent);

	// SRVをコマンドに積む
	SRVManager::SetGraphicsRootDescriptorTable(3, srv_);

	// 描画
	commands.List->DrawInstanced(3, 1, 0, 0);
}