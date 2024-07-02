#include "IPostEffect.h"



// ImGuiの描画
void IPostEffect::DrawImGui()
{
	if (ImGui::TreeNode("PostEffect")) {

		ImGui::ColorEdit4("Color", &material_.mtlData.color.x);
		/*if (ImGui::Button("None")) {
			effectType_ = IPostEffect::Type::None;
		}*/
		if (ImGui::Button("BoxFileter")) {
			effectType_ = IPostEffect::Type::BoxFilter;
		}
		/*if (ImGui::Button("ColorGrading")) {
			effectType_ = IPostEffect::Type::ColorGrading;
		}*/
		if (ImGui::Button("Dissolve")) {
			effectType_ = IPostEffect::Type::Dissolve;
		}
		if (ImGui::Button("GaussianFilter")) {
			effectType_ = IPostEffect::Type::GaussianFilter;
		}
		if (ImGui::Button("GrayScale")) {
			effectType_ = IPostEffect::Type::GrayScale;
		}
		if (ImGui::Button("OutLine")) {
			effectType_ = IPostEffect::Type::OutLine;
		}
		if (ImGui::Button("RadialBlur")) {
			effectType_ = IPostEffect::Type::RadialBlur;
		}
		if (ImGui::Button("Random")) {
			effectType_ = IPostEffect::Type::Random;
		}
		if (ImGui::Button("SepiaTone")) {
			effectType_ = IPostEffect::Type::SepiaTone;
		}
		if (ImGui::Button("Vignetting")) {
			effectType_ = IPostEffect::Type::Vignetting;
		}

		ImGui::TreePop();
	}
}


// リソース作成
void IPostEffect::Create()
{
	// マテリアル作成
	material_.Create();
	vignettingMtl_.Create();

	ComPtr<ID3D12Resource> stv = RTVManager::GetRTV("PostEffect")->GetRTVPrope().Resources.Get();
	//srv_ = DescriptorManager::CreateRenderTextureSRV(stv);
	srv_ = SRVManager::CreatePostEffectSRV(stv);
	//srv_ = DescriptorManager::CreateRenderTextureDepthSRV(stv);
}


// コマンドコール
void IPostEffect::CommandCall(Camera* camera)
{
	// コマンドの取得
	Commands commands = CommandManager::GetInstance()->GetCommands();

	// PipeLineCheck
	PipeLineCheck();

	// Materialの設定
	if (effectType_ == IPostEffect::Type::Vignetting) {
		vignettingMtl_.TransferMaterial();
		commands.List->SetGraphicsRootConstantBufferView(4, vignettingMtl_.constBuffer->GetGPUVirtualAddress());
	}
	else {
		material_.mtlData.projectionInverse = camera->projectionInverseMatrix;
		material_.TransferMaterial();
		commands.List->SetGraphicsRootConstantBufferView(4, material_.constBuffer->GetGPUVirtualAddress());
	}
	
	// DescriptorTableの設定
	//DescriptorManager::SetGraphicsRootDescriptorTable(3, srv_);
	SRVManager::SetGraphicsRootDescriptorTable(3, srv_);

	// 頂点3つ描画
	commands.List->DrawInstanced(3, 1, 0, 0);
}


// PipeLineチェック
void IPostEffect::PipeLineCheck()
{
	switch (effectType_) {

	case IPostEffect::Type::None:

		assert(false && "Effect type is None. Please set a valid effect type.");
		break;

	case IPostEffect::Type::BoxFilter:

		PipeLineManager::PipeLineCheckAndSet(PipeLineType::BoxFilter);
		break;

	case IPostEffect::Type::ColorGrading:

		//PipeLineManager::PipeLineCheckAndSet(PipeLineType::ColorGrading);
		assert(false && "Effect type is None. Please set a valid effect type.");
		break;

	case IPostEffect::Type::Dissolve:

		PipeLineManager::PipeLineCheckAndSet(PipeLineType::Dissolve);
		break;

	case IPostEffect::Type::GaussianFilter:

		PipeLineManager::PipeLineCheckAndSet(PipeLineType::GaussianFilter);
		break;

	case IPostEffect::Type::GrayScale:

		PipeLineManager::PipeLineCheckAndSet(PipeLineType::GrayScale);
		break;

	case IPostEffect::Type::OutLine:

		PipeLineManager::PipeLineCheckAndSet(PipeLineType::OutLine);
		break;

	case IPostEffect::Type::RadialBlur:

		PipeLineManager::PipeLineCheckAndSet(PipeLineType::RadialBlur);
		break;

	case IPostEffect::Type::Random:

		PipeLineManager::PipeLineCheckAndSet(PipeLineType::Random);
		break;

	case IPostEffect::Type::SepiaTone:

		PipeLineManager::PipeLineCheckAndSet(PipeLineType::SepiaTone);
		break;

	case IPostEffect::Type::Vignetting:

		PipeLineManager::PipeLineCheckAndSet(PipeLineType::Vignetting);
		break;

	default:
		// その他の処理
		assert(false && "Unknown effect type.");
		break;
	}
}
