#pragma once

#include <d3dx12.h>
#include <dxcapi.h>

#include "../../../Project/Math/MyMath.h"
#include "../../../Project/Math/Struct.h"
#include "../../Base/DXCommon/DirectXCommon.h"
#include "../ShaderManager/ShaderManager.h"

#include "IPipeLineState/IPipeLineState.h"

#include "Normal/NormalGraphicPipeline.h"
#include "Object3D/Object3DGraphicPipeLine.h"
#include "Sprite/SpriteGraphicPipeline.h"
#include "Light/LightGraphicPipeline.h"
#include "Lambert/LambertGraphicPipeline.h"
#include "Phong/PhongGraphicPipeline.h"
#include "PhongNormalMap/PhongNormalMap.h"
#include "Particle/ParticleGraphicPipeline.h"
#include "Line/LineGraphicPipeline.h"
#include "PostEffect/PostEffectGraphicPipeline.h"

#include "ModelPipeLine/LambertPipeLine/LambertPipeLine.h"
#include "ModelPipeLine/LightPipeLine/LightPipeLine.h"
#include "ModelPipeLine/LinePipeLine/LinePipeLine.h"
#include "ModelPipeLine/NormalPipeLine/NormalPipeLine.h"
#include "ModelPipeLine/Object3DPipeLine/Object3DPipeLine.h"
#include "ModelPipeLine/ParticlePipeLine/ParticlePipeLine.h"
#include "ModelPipeLine/PhongNormalMapPipeLine/PhongNormalMapPipeLine.h"
#include "ModelPipeLine/PhongPipeLine/PhongPipeLine.h"
#include "ModelPipeLine/SpritePipeLine/SpritePipeLine.h"

#include "PostEffectPipeLine/BoxFilterPipeLine/BoxFilterPipeLine.h"
#include "PostEffectPipeLine/DissolvePipeLine/DissolvePipeLine.h"
#include "PostEffectPipeLine/GaussianFilterPipeLine/GaussianFilterPipeLine.h"
#include "PostEffectPipeLine/GrayScalePipeLine/GrayScalePipeLine.h"
#include "PostEffectPipeLine/OutLinePipeLine/OutLinePipeLine.h"
#include "PostEffectPipeLine/RadialBlurPipeLine/RadialBlurPipeLine.h"
#include "PostEffectPipeLine/RandomPipeLine/RandomPipeLine.h"
#include "PostEffectPipeLine/SepiaTonePipeLine/SepiaTonePipeLine.h"
#include "PostEffectPipeLine/VignettingPipeLine/VignettingPipeLine.h"


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

	//// Lambert
	//std::unique_ptr<LambertPipeLine> lambertPipeLine_;

	//// Light
	//std::unique_ptr<LightPipeLine> lightPipeLine_;

	//// Line
	//std::unique_ptr<LinePipeLine> linePipeLine_;

	//// Normal
	//std::unique_ptr<NormalPipeLine> normalPipeLine_;
	//
	//// Object3D
	//std::unique_ptr<Object3DPipeLine> object3DPipeLine_;

	//// Particle
	//std::unique_ptr<ParticlePipeLine> particlePipeLine_;

	//// PhongNormalMap
	//std::unique_ptr<PhongNormalMapPipeLine> phongNormalMapPipeLine_;

	//// Phong
	//std::unique_ptr<PhongPipeLine> phongPipeLine_;

	//// Sprite
	//std::unique_ptr<SpritePipeLine> spritePipeLine_;

	//// BoxFilter
	//std::unique_ptr<BoxFilterPipeLine> boxFilterPipeLine_;

	//// Dissolve
	//std::unique_ptr<DissolvePipeLine> dissolvePipeLine_;

	//// GaussianFilter
	//std::unique_ptr<GaussianFilterPipeLine> gaussianFilterPipeLine_;

	//// GrayScale
	//std::unique_ptr<GrayScalePipeLine> grayScalePipeLine_;

	//// OutLine
	//std::unique_ptr<OutLinePipeLine> outLinePipeLine_;

	//// RadialBlur
	//std::unique_ptr<RadialBlurPipeLine> radialBlurPipeLine_;

	//// Random
	//std::unique_ptr<RandomPipeLine> randomPipeLine_;

	//// SepiaTone
	//std::unique_ptr<SepiaTonePipeLine> sepiaTonePipeLine_;

	//// Vignetting
	//std::unique_ptr<VignettingPipeLine> vignettingPipeLine_;

};