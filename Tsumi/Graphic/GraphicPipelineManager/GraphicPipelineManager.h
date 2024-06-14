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

	// PipeLineを保存しておくvectorコンテナ
	std::vector<PsoProperty> IPipeLine_;

	// Lambert
	unique_ptr<LambertPipeLine> lambertPipeLine_;

	// Light
	unique_ptr<LightPipeLine> lightPipeLine_;

	// Line
	unique_ptr<LinePipeLine> linePipeLine_;

	// Normal
	unique_ptr<NormalPipeLine> normalPipeLine_;
	
	// Object3D
	unique_ptr<Object3DPipeLine> object3DPipeLine_;

	// Particle
	unique_ptr<ParticlePipeLine> particlePipeLine_;

	// PhongNormalMap
	unique_ptr<PhongNormalMapPipeLine> phongNormalMapPipeLine_;

	// Phong
	unique_ptr<PhongPipeLine> phongPipeLine_;

	// Sprite
	unique_ptr<SpritePipeLine> spritePipeLine_;

	// BoxFilter
	unique_ptr<BoxFilterPipeLine> boxFilterPipeLine_;

	// Dissolve
	unique_ptr<DissolvePipeLine> dissolvePipeLine_;

	// GaussianFilter
	unique_ptr<GaussianFilterPipeLine> gaussianFilterPipeLine_;

	// GrayScale
	unique_ptr<GrayScalePipeLine> grayScalePipeLine_;

	// OutLine
	unique_ptr<OutLinePipeLine> outLinePipeLine_;

	// RadialBlur
	unique_ptr<RadialBlurPipeLine> radialBlurPipeLine_;

	// Random
	unique_ptr<RandomPipeLine> randomPipeLine_;

	// SepiaTone
	unique_ptr<SepiaTonePipeLine> sepiaTonePipeLine_;

	// Vignetting
	unique_ptr<VignettingPipeLine> vignettingPipeLine_;

};