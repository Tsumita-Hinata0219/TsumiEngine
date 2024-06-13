#pragma once

#include <d3dx12.h>
#include <dxcapi.h>

#include "MyMath.h"
#include "Struct.h"
#include "DirectXCommon.h"
#include "ShaderManager.h"

#include "IPipeLineState.h"

#include "NormalGraphicPipeline.h"
#include "Object3DGraphicPipeLine.h"
#include "SpriteGraphicPipeline.h"
#include "LightGraphicPipeline.h"
#include "LambertGraphicPipeline.h"
#include "PhongGraphicPipeline.h"
#include "PhongNormalMap.h"
#include "ParticleGraphicPipeline.h"
#include "LineGraphicPipeline.h"
#include "PostEffectGraphicPipeline.h"

#include "LambertPipeLine.h"
#include "LightPipeLine.h"
#include "LinePipeLine.h"
#include "NormalPipeLine.h"
#include "Object3DPipeLine.h"
#include "ParticlePipeLine.h"
#include "PhongNormalMapPipeLine.h"
#include "PhongPipeLine.h"
#include "SpritePipeLine.h"

#include "BoxFilterPipeLine.h"
#include "DissolvePipeLine.h"
#include "GaussianFilterPipeLine.h"
#include "GrayScalePipeLine.h"
#include "OutLinePipeLine.h"
#include "RadialBlurPipeLine.h"
#include "RandomPipeLine.h"
#include "SepiaTonePipeLine.h"
#include "VignettingPipeLine.h"


class GraphicPipelineManager {

public: // メンバ関数

	/// <summary>
	/// PSOクラスのインスタンス取得
	/// </summary>
	static GraphicPipelineManager* GetInstance();

	/// <summary>
	/// 初期化処理
	/// </summary>
	static void Initialize();


private: // メンバ変数

	std::vector<unique_ptr<IPipeLineState>> IPipeLine_;


};