#include "IPostEffect.h"



// ImGuiの描画
void IPostEffect::DrawImGui()
{
	if (ImGui::TreeNode("PostEffect")) {

		// std::vector<std::string>をstd::vector<const char*>に変換
		std::vector<const char*> cstrEffectNames;
		for (const auto& name : imguiEffectName_) {
			cstrEffectNames.push_back(name.c_str());
		}

		if (ImGui::Combo("EffectType", &imguiComboIndex_, cstrEffectNames.data(), int(cstrEffectNames.size()))) {
			
			switch (imguiComboIndex_) {
			case 0: effectType_ = IPostEffect::Type::Absent; break;
			case 1: effectType_ = IPostEffect::Type::BoxFilter; break;
			case 2: effectType_ = IPostEffect::Type::ColorGrading; break;
			case 3: effectType_ = IPostEffect::Type::Dissolve; break;
			case 4: effectType_ = IPostEffect::Type::GaussianFilter; break;
			case 5: effectType_ = IPostEffect::Type::Grain; break;
			case 6: effectType_ = IPostEffect::Type::GrayScale; break;
			case 7: effectType_ = IPostEffect::Type::OutLine; break;
			case 8: effectType_ = IPostEffect::Type::RadialBlur; break;
			case 9: effectType_ = IPostEffect::Type::Random; break;
			case 10: effectType_ = IPostEffect::Type::SepiaTone; break;
			case 11: effectType_ = IPostEffect::Type::Vignetting; break;
			}
		}
		ImGui::TreePop();
	}
}


// リソース作成
void IPostEffect::Create()
{
	// IPostEffect::Typeを表す文字
	imguiEffectName_ = {
		"Absent",
		"BoxFilter",
		"ColorGrading",
		"Dissolve",
		"GaussianFilter",
		"Grain",
		"GrayScale",
		"LuminanceOutLine",
		"RadialBlur",
		"Random",
		"SepiaTone",
		"Vignetting"
	};

	// マテリアル作成
	material_.Create();
	vignettingMtl_.Create();

	// マテリアルのバッファ作成
	boxFilterBuffer_.CreateResource();
	colorGradingBuffer_.CreateResource();
	dissolveBuffer_.CreateResource();
	dissolveBuffer_.CreateResource();
	gaussianFilterBuffer_.CreateResource();
	grainBuffer_.CreateResource();
	grayScaleBuffer_.CreateResource();
	outLineBuffer_.CreateResource();
	radialBlurBuffer_.CreateResource();
	randomBuffer_.CreateResource();
	sepiaToneBuffer_.CreateResource();
	vignettingBuffer_.CreateResource();


	ComPtr<ID3D12Resource> stv = RTVManager::GetRTV("PostEffect")->GetRTVPrope().Resources.Get();
	srv_ = DescriptorManager::CreateRenderTextureSRV(stv);
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
	DescriptorManager::SetGraphicsRootDescriptorTable(3, srv_);

	// 頂点3つ描画
	commands.List->DrawInstanced(3, 1, 0, 0);
}


// PipeLineチェック
void IPostEffect::PipeLineCheck()
{
	switch (effectType_) {

	case IPostEffect::Type::Absent:

		PipeLineManager::PipeLineCheckAndSet(PipeLineType::Absent);
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

	case IPostEffect::Type::Grain:

		PipeLineManager::PipeLineCheckAndSet(PipeLineType::Grain);
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
