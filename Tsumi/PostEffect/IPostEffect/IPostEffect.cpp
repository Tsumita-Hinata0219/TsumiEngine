#include "IPostEffect.h"


// リソース作成
void IPostEffect::Create()
{
	// マテリアル作成
	material_.Create();

	ComPtr<ID3D12Resource> stv = RTVManager::GetRTV("PostEffect")->GetRTVPrope().Resources.Get();
	srv_ = DescriptorManager::CreateRenderTextureSRV(stv);
}


// コマンドコール
void IPostEffect::CommandCall()
{
	// コマンドの取得
	Commands commands = DirectXCommon::GetInstance()->GetCommands();

	// Materialの設定
	material_.TransferMaterial();
	commands.List->SetGraphicsRootConstantBufferView(0, material_.constBuffer->GetGPUVirtualAddress());

	// DescriptorTableの設定
	DescriptorManager::SetGraphicsRootDescriptorTable(3, srv_);

	// 頂点3つ描画
	commands.List->DrawInstanced(3, 1, 0, 0);
}
