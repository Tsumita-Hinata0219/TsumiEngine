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

	NormalGraphicPipeline::SetupNormalPso();
	SpriteGraphicPipeline::SetupSpritePso();
	LightGraphicPipeline::SetupLightPso();
	ParticleGraphicPipeline::SetupParticlePso();
}


