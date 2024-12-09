#include "PipeLineManager.h"


// PipeLineType
PipeLineType PipeLineManager::nowPipeLineType_ = PipeLineType::None;


// 初期化処理
void PipeLineManager::Initialize()
{
	// インスタンスの取得
	PipeLineManager* instance = PipeLineManager::GetInstance();


	// Object2D
	instance->object2DPipeLine_ = make_unique<Object2DPipeLine>();
	instance->pipeLineMap_[PipeLineType::Object2D] = instance->object2DPipeLine_->SetUpPso();

	// Object3D
	instance->object3DPipeLine_ = make_unique<Object3DPipeLine>();
	instance->pipeLineMap_[PipeLineType::Object3D] = instance->object3DPipeLine_->SetUpPso();

	// SkinningObject3d
	instance->skinningObject3DPipeLine_ = make_unique<SkinningObject3dPipeLine>();
	instance->pipeLineMap_[PipeLineType::SkinningObject3D] = instance->skinningObject3DPipeLine_->SetUpPso();

	// Skybox
	instance->skyboxPipeLine_ = make_unique<SkyboxPipeLine>();
	instance->pipeLineMap_[PipeLineType::Skybox] = instance->skyboxPipeLine_->SetUpPso();

	// CPUParticle
	instance->cpuParticlePipeLine_ = make_unique<CPUParticlePipeLine>();
	instance->pipeLineMap_[PipeLineType::CPUParticle] = instance->cpuParticlePipeLine_->SetUpPso();

	// GPUParticle_Init
	instance->gParticle_Init_PipeLine_ = make_unique<GPUParticle_Init_PipeLine>();
	instance->pipeLineMap_[PipeLineType::GPUParticle_Init] = instance->gParticle_Init_PipeLine_->SetUpPso();

	// GPUParticle_Draw
	instance->gParticle_Draw_PipeLine_ = make_unique<GPUParticle_Draw_PipeLine>();
	instance->pipeLineMap_[PipeLineType::GPUParticle_Draw] = instance->gParticle_Draw_PipeLine_->SetUpPso();

	// Absent
	instance->absentPipeLine_ = make_unique<AbsentPipeLine>();
	instance->pipeLineMap_[PipeLineType::Absent] = instance->absentPipeLine_->SetUpPso();

	// BoxFilter
	instance->boxFilterPipeLine_ = make_unique<BoxFilterPipeLine>();
	instance->pipeLineMap_[PipeLineType::BoxFilter] = instance->boxFilterPipeLine_->SetUpPso();

	// Dissolve
	instance->dissolvePipeLine_ = make_unique<DissolvePipeLine>();
	instance->pipeLineMap_[PipeLineType::Dissolve] = instance->dissolvePipeLine_->SetUpPso();

	// GaussianFilter
	instance->gaussianFilterPipeLine_ = make_unique<GaussianFilterPipeLine>();
	instance->pipeLineMap_[PipeLineType::GaussianFilter] = instance->gaussianFilterPipeLine_->SetUpPso();

	// Glitch
	instance->glitchPipeLine_ = make_unique<GlitchPipeLine>();
	instance->pipeLineMap_[PipeLineType::Glitch] = instance->glitchPipeLine_->SetUpPso();

	// Grain
	instance->grainPipeLine_ = make_unique<GrainPipeLine>();
	instance->pipeLineMap_[PipeLineType::Grain] = instance->grainPipeLine_->SetUpPso();

	// GrayScale
	instance->grayScalePipeLine_ = make_unique<GrayScalePipeLine>();
	instance->pipeLineMap_[PipeLineType::GrayScale] = instance->grayScalePipeLine_->SetUpPso();

	// HSV
	instance->hsvPipeLine_ = make_unique<HSVPipeLine>();
	instance->pipeLineMap_[PipeLineType::HSV] = instance->hsvPipeLine_->SetUpPso();

	// OutLine
	instance->outLinePipeLine_ = make_unique<OutLinePipeLine>();
	instance->pipeLineMap_[PipeLineType::OutLine] = instance->outLinePipeLine_->SetUpPso();

	// RadialBlur
	instance->radialBlurPipeLine_ = make_unique<RadialBlurPipeLine>();
	instance->pipeLineMap_[PipeLineType::RadialBlur] = instance->radialBlurPipeLine_->SetUpPso();

	// Randome
	instance->randomPipeLine_ = make_unique<RandomPipeLine>();
	instance->pipeLineMap_[PipeLineType::Random] = instance->randomPipeLine_->SetUpPso();

	// RetroCRT
	instance->retroCRTPipeLine_ = make_unique<RetroCRTPipeLine>();
	instance->pipeLineMap_[PipeLineType::RetroCRT] = instance->retroCRTPipeLine_->SetUpPso();

	// SepiaTone
	instance->sepiaTonePipeLine_ = make_unique<SepiaTonePipeLine>();
	instance->pipeLineMap_[PipeLineType::SepiaTone] = instance->sepiaTonePipeLine_->SetUpPso();

	// Vignetting
	instance->vignettingPipeLine_ = make_unique<VignettingPipeLine>();
	instance->pipeLineMap_[PipeLineType::Vignetting] = instance->vignettingPipeLine_->SetUpPso();

	// CSParticle
	instance->csParticlePipeLine_ = make_unique<CSParticlePipeLine>();
	instance->pipeLineMap_[PipeLineType::CSParticle] = instance->csParticlePipeLine_->SetUpPso();
}


// PipeLineのチェックと設定
void PipeLineManager::PipeLineCheckAndSet(const PipeLineType type, bool state)
{
	// PipeLineTypeが違っていたらcommandを再設定
	if (nowPipeLineType_ != type) {

		// Commandの取得
		Commands commands = CommandManager::GetInstance()->GetCommands();

		// このクラスのインスタンスの取得
		PipeLineManager* instance = PipeLineManager::GetInstance();

		// nowPipeLineTypeの再設定
		nowPipeLineType_ = type;

		if (state) {
			// 引数typeにあったPipeLineを積みなおす
			commands.List->SetGraphicsRootSignature(instance->pipeLineMap_[type].rootSignature);
			commands.List->SetPipelineState(instance->pipeLineMap_[type].graphicsPipelineState);
			// 形状を設定。基本PipeLineで設定したものと同じもの
			commands.List->IASetPrimitiveTopology(instance->pipeLineMap_[type].primitiveTopologyType);
		}
		else {
			// 引数typeにあったPipeLineを積みなおす
			commands.List->SetComputeRootSignature(instance->pipeLineMap_[type].rootSignature);
			commands.List->SetPipelineState(instance->pipeLineMap_[type].graphicsPipelineState);
		}
	}
}

