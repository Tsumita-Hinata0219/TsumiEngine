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

	// インスタンスの取得
	GraphicPipelineManager* instance = GraphicPipelineManager::GetInstance();

	// vectorのサイズを変える
	instance->IPipeLine_.resize(EnumSize<IPipeLineType>::value);
	instance->IPipeLine_[static_cast<size_t>(IPipeLineType::Normal)];


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
}


