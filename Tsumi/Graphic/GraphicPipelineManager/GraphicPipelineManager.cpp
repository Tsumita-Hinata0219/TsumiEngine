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


	// Lambert
	instance->lambertPipeLine_ = make_unique<LambertPipeLine>();
	instance->pipeLineMap_[PipeLineType::Lambert] = instance->lambertPipeLine_->SetUpPso();

	// Light
	instance->lightPipeLine_ = make_unique<LightPipeLine>();
	instance->pipeLineMap_[PipeLineType::Light] = instance->lightPipeLine_->SetUpPso();

	// Line
	instance->linePipeLine_ = make_unique<LinePipeLine>();
	instance->pipeLineMap_[PipeLineType::Line] = instance->linePipeLine_->SetUpPso();

	//// Normal
	//instance->normalPipeLine_ = make_unique<NormalPipeLine>();
	//instance->pipeLineMap_[PipeLineType::Normal] = instance->normalPipeLine_->SetUpPso();

	// Object3D
	instance->object3DPipeLine_ = make_unique<Object3DPipeLine>();
	instance->pipeLineMap_[PipeLineType::Object3D] = instance->object3DPipeLine_->SetUpPso();

	// Particle
	instance->particlePipeLine_ = make_unique<ParticlePipeLine>();
	instance->pipeLineMap_[PipeLineType::Particle] = instance->particlePipeLine_->SetUpPso();

	// PhongNormalMap
	instance->phongNormalMapPipeLine_ = make_unique<PhongNormalMapPipeLine>();
	instance->pipeLineMap_[PipeLineType::PhongNormalMap] = instance->phongNormalMapPipeLine_->SetUpPso();

	// Phong
	instance->phongPipeLine_ = make_unique<PhongPipeLine>();
	instance->pipeLineMap_[PipeLineType::Phong] = instance->phongPipeLine_->SetUpPso();

	// Sprite
	instance->spritePipeLine_ = make_unique<SpritePipeLine>();
	instance->pipeLineMap_[PipeLineType::Sprite] = instance->spritePipeLine_->SetUpPso();

	// BoxFilter
	instance->spritePipeLine_ = make_unique<SpritePipeLine>();
	instance->pipeLineMap_[PipeLineType::Sprite] = instance->spritePipeLine_->SetUpPso();

	// Dissolve
	instance->spritePipeLine_ = make_unique<SpritePipeLine>();
	instance->pipeLineMap_[PipeLineType::Sprite] = instance->spritePipeLine_->SetUpPso();

	// GaussianFilter
	instance->spritePipeLine_ = make_unique<SpritePipeLine>();
	instance->pipeLineMap_[PipeLineType::Sprite] = instance->spritePipeLine_->SetUpPso();

	// GrayScale
	instance->spritePipeLine_ = make_unique<SpritePipeLine>();
	instance->pipeLineMap_[PipeLineType::Sprite] = instance->spritePipeLine_->SetUpPso();

	// OutLine
	instance->spritePipeLine_ = make_unique<SpritePipeLine>();
	instance->pipeLineMap_[PipeLineType::Sprite] = instance->spritePipeLine_->SetUpPso();

	// RadialBlur
	instance->spritePipeLine_ = make_unique<SpritePipeLine>();
	instance->pipeLineMap_[PipeLineType::Sprite] = instance->spritePipeLine_->SetUpPso();

	// Randome
	instance->spritePipeLine_ = make_unique<SpritePipeLine>();
	instance->pipeLineMap_[PipeLineType::Sprite] = instance->spritePipeLine_->SetUpPso();

	// SepiaTone
	instance->spritePipeLine_ = make_unique<SpritePipeLine>();
	instance->pipeLineMap_[PipeLineType::Sprite] = instance->spritePipeLine_->SetUpPso();

	// Vignetting
	instance->spritePipeLine_ = make_unique<SpritePipeLine>();
	instance->pipeLineMap_[PipeLineType::Sprite] = instance->spritePipeLine_->SetUpPso();


}


