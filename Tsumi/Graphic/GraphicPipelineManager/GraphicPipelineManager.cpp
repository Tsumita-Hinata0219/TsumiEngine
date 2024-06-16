#include "GraphicPipelineManager.h"


/// <summary>
/// PSOクラスのインスタンス取得
/// </summary>
GraphicPipelineManager* GraphicPipelineManager::GetInstance() {

	static GraphicPipelineManager instance;
	return &instance;
}



/// <summary>
/// 初期化処理
/// </summary>
void GraphicPipelineManager::Initialize() {

	//NormalGraphicPipeline::SetupNormalPso();
	SpriteGraphicPipeline::SetupSpritePso();
	LightGraphicPipeline::SetupLightPso();
	LambertGraphicPipeline::SetupLightPso();
	PhongGraphicPipeline::SetupLightPso();
	PhongNormalMap::SetupLightPso();
	ParticleGraphicPipeline::SetupParticlePso();
	LineGraphicPipeline::SetupLightPso();
	Object3DGraphicPipeLine::SetupObject3DPso();
	PostEffectGraphicPipeline::SetupPostEffectPso();


	// インスタンスの取得
	GraphicPipelineManager* instance = GraphicPipelineManager::GetInstance();

	// vectorのサイズを変える
	instance->IPipeLine_.resize(EnumSize<IPipeLineType>::value);


	//// Lambert
	//instance->lambertPipeLine_ = make_unique<LambertPipeLine>();
	//instance->IPipeLine_[static_cast<size_t>(IPipeLineType::Lambert)] = instance->lambertPipeLine_->SetUpPso();

	//// Light
	//instance->lightPipeLine_ = make_unique<LightPipeLine>();
	//instance->IPipeLine_[static_cast<size_t>(IPipeLineType::Light)] = instance->lightPipeLine_->SetUpPso();

	//// Line
	//instance->linePipeLine_ = make_unique<LinePipeLine>();
	//instance->IPipeLine_[static_cast<size_t>(IPipeLineType::Line)] = instance->linePipeLine_->SetUpPso();

	//// Normal
	//instance->normalPipeLine_ = make_unique<NormalPipeLine>();
	//instance->IPipeLine_[static_cast<size_t>(IPipeLineType::Normal)] = instance->normalPipeLine_->SetUpPso();

	//// Object3D
	//instance->object3DPipeLine_ = make_unique<Object3DPipeLine>();
	//instance->IPipeLine_[static_cast<size_t>(IPipeLineType::Object3D)] = instance->object3DPipeLine_->SetUpPso();

	//// Particle
	//instance->particlePipeLine_ = make_unique<ParticlePipeLine>();
	//instance->IPipeLine_[static_cast<size_t>(IPipeLineType::Particle)] = instance->particlePipeLine_->SetUpPso();

	//// PhongNormalMap
	//instance->phongNormalMapPipeLine_ = make_unique<PhongNormalMapPipeLine>();
	//instance->IPipeLine_[static_cast<size_t>(IPipeLineType::PhongNormalMap)] = instance->phongNormalMapPipeLine_->SetUpPso();

	//// Phong
	//instance->phongPipeLine_ = make_unique<PhongPipeLine>();
	//instance->IPipeLine_[static_cast<size_t>(IPipeLineType::Phong)] = instance->phongPipeLine_->SetUpPso();

	//// Sprite
	//instance->spritePipeLine_ = make_unique<SpritePipeLine>();
	//instance->IPipeLine_[static_cast<size_t>(IPipeLineType::Sprite)] = instance->spritePipeLine_->SetUpPso();

	//// BoxFilter
	//instance->boxFilterPipeLine_ = make_unique<BoxFilterPipeLine>();
	//instance->IPipeLine_[static_cast<size_t>(IPipeLineType::BoxFilter)] = instance->boxFilterPipeLine_->SetUpPso();

	//// Dissolve
	//instance->dissolvePipeLine_ = make_unique<DissolvePipeLine>();
	//instance->IPipeLine_[static_cast<size_t>(IPipeLineType::Dissolve)] = instance->dissolvePipeLine_->SetUpPso();

	//// GaussianFilter
	//instance->gaussianFilterPipeLine_ = make_unique<GaussianFilterPipeLine>();
	//instance->IPipeLine_[static_cast<size_t>(IPipeLineType::GaussianFilter)] = instance->gaussianFilterPipeLine_->SetUpPso();

	//// GrayScale
	//instance->grayScalePipeLine_ = make_unique<GrayScalePipeLine>();
	//instance->IPipeLine_[static_cast<size_t>(IPipeLineType::GrayScale)] = instance->grayScalePipeLine_->SetUpPso();

	//// OutLine
	//instance->outLinePipeLine_ = make_unique<OutLinePipeLine>();
	//instance->IPipeLine_[static_cast<size_t>(IPipeLineType::OutLine)] = instance->outLinePipeLine_->SetUpPso();

	//// RadialBlur
	//instance->radialBlurPipeLine_ = make_unique<RadialBlurPipeLine>();
	//instance->IPipeLine_[static_cast<size_t>(IPipeLineType::RadialBlur)] = instance->radialBlurPipeLine_->SetUpPso();

	//// Randome
	//instance->randomPipeLine_ = make_unique<RandomPipeLine>();
	//instance->IPipeLine_[static_cast<size_t>(IPipeLineType::Random)] = instance->randomPipeLine_->SetUpPso();

	//// SepiaTone
	//instance->sepiaTonePipeLine_ = make_unique<SepiaTonePipeLine>();
	//instance->IPipeLine_[static_cast<size_t>(IPipeLineType::SepiaTone)] = instance->sepiaTonePipeLine_->SetUpPso();

	//// Vignetting
	//instance->vignettingPipeLine_ = make_unique<VignettingPipeLine>();
	//instance->IPipeLine_[static_cast<size_t>(IPipeLineType::Vignetting)] = instance->vignettingPipeLine_->SetUpPso();
}


