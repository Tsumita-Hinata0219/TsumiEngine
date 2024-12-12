#pragma once


#include <d3dx12.h>
#include <dxcapi.h>

#include "Math/MyMath.h"
#include "Math/Struct.h"
#include "../Base/DXCommon/DirectXCommon.h"
#include "../ShaderManager/ShaderManager.h"
#include "../CommandManager/CommandManager.h"

#include "IPipeLineState/IPipeLineState.h"

#include "ModelPipeLine/Object2DPipeLine/Object2DPipeLine.h"
#include "ModelPipeLine/Object3DPipeLine/Object3DPipeLine.h"
#include "ModelPipeLine/SkinningObject3dPipeLine/SkinningObject3dPipeLine.h"
#include "ModelPipeLine/SkyboxPipeLine/SkyboxPipeLine.h"
#include "ModelPipeLine/CPUParticlePipeLine/CPUParticlePipeLine.h"
#include "ModelPipeLine/GPUParticle_Draw/GPUParticle_Draw_PipeLine.h"

#include "PostEffectPipeLine/AbsentPipeLine/AbsentPipeLine.h"
#include "PostEffectPipeLine/BoxFilterPipeLine/BoxFilterPipeLine.h"
#include "PostEffectPipeLine/DissolvePipeLine/DissolvePipeLine.h"
#include "PostEffectPipeLine/GaussianFilterPipeLine/GaussianFilterPipeLine.h"
#include "PostEffectPipeLine/GlitchPipeLine/GlitchPipeLine.h"
#include "PostEffectPipeLine/GrayScalePipeLine/GrayScalePipeLine.h"
#include "PostEffectPipeLine/HSVPipeLine/HSVPipeLine.h"
#include "PostEffectPipeLine/OutLinePipeLine/OutLinePipeLine.h"
#include "PostEffectPipeLine/RadialBlurPipeLine/RadialBlurPipeLine.h"
#include "PostEffectPipeLine/RandomPipeLine/RandomPipeLine.h"
#include "PostEffectPipeLine/RetroCRTPipeLine/RetroCRTPipeLine.h"
#include "PostEffectPipeLine/SepiaTonePipeLine/SepiaTonePipeLine.h"
#include "PostEffectPipeLine/VignettingPipeLine/VignettingPipeLine.h"
#include "PostEffectPipeLine/GrainPipeLine/GrainPipeLine.h"

#include "CSPipeLine/Particle/CSParticlePipeLine.h"
#include "CSPipeLine/GPUParticle/Init/GPUParticle_Init_PipeLine.h"


// PipeLineTypeのenum構造体
enum class PipeLineType : uint32_t {
	None,
	Object2D,
	Object3D,
	SkinningObject3D,
	Skybox,
	CPUParticle,
	GPUParticle_Init,
	GPUParticle_Draw,
	PostEffect,
	Absent,
	BoxFilter,
	Dissolve,
	GaussianFilter,
	Glitch,
	Grain,
	GrayScale,
	HSV,
	OutLine,
	RadialBlur,
	Random,
	RetroCRT,
	SepiaTone,
	Vignetting,
	CSParticle,
};



/* PipeLineManagerクラス */
class PipeLineManager {

public: // メンバ関数

	// インスタンスの取得
	static PipeLineManager* GetInstance() {
		static PipeLineManager instance;
		return &instance;
	}

	// 初期化処理
	static void Initialize();

	// PipeLineのチェックと設定
	static void PipeLineCheckAndSet(const PipeLineType type, bool state = true);

	// PipeLineTypeのリセット
	static void PipeLineTypeReset() {
		nowPipeLineType_ = PipeLineType::None;
	}

#pragma region Accessor アクセッサ

	// PipeLineの取得
	PsoProperty GetPipeLine(PipeLineType type) {
		return pipeLineMap_[type];
	}

#pragma endregion


private: // メンバ変数

	// PipeLineのタイプ
	static PipeLineType nowPipeLineType_;

	// PipeLineを保存しておくmapコンテナ
	std::map<PipeLineType, PsoProperty> pipeLineMap_;

	// Object2D
	std::unique_ptr<Object2DPipeLine> object2DPipeLine_;

	// Object3D
	std::unique_ptr<Object3DPipeLine> object3DPipeLine_;

	// SkinningObject3d
	std::unique_ptr<SkinningObject3dPipeLine> skinningObject3DPipeLine_;

	// Skybox
	std::unique_ptr<SkyboxPipeLine> skyboxPipeLine_;

	// CPUParticle
	std::unique_ptr<CPUParticlePipeLine> cpuParticlePipeLine_;

	// GPUParticle_Init
	std::unique_ptr<GPUParticle_Init_PipeLine> gParticle_Init_PipeLine_;

	// GPUParticle_ Draw
	std::unique_ptr<GPUParticle_Draw_PipeLine> gParticle_Draw_PipeLine_;

	// Absent
	std::unique_ptr<AbsentPipeLine> absentPipeLine_;

	// BoxFilter
	std::unique_ptr<BoxFilterPipeLine> boxFilterPipeLine_;

	// Dissolve
	std::unique_ptr<DissolvePipeLine> dissolvePipeLine_;

	// GaussianFilter
	std::unique_ptr<GaussianFilterPipeLine> gaussianFilterPipeLine_;

	// Glitch
	std::unique_ptr<GlitchPipeLine> glitchPipeLine_;

	// Grain
	std::unique_ptr<GrainPipeLine> grainPipeLine_;

	// GrayScale
	std::unique_ptr<GrayScalePipeLine> grayScalePipeLine_;

	// HSV
	std::unique_ptr<HSVPipeLine> hsvPipeLine_;

	// OutLine
	std::unique_ptr<OutLinePipeLine> outLinePipeLine_;

	// RadialBlur
	std::unique_ptr<RadialBlurPipeLine> radialBlurPipeLine_;

	// Random
	std::unique_ptr<RandomPipeLine> randomPipeLine_;

	// RetroCRT
	std::unique_ptr<RetroCRTPipeLine> retroCRTPipeLine_;

	// SepiaTone
	std::unique_ptr<SepiaTonePipeLine> sepiaTonePipeLine_;

	// Vignetting
	std::unique_ptr<VignettingPipeLine> vignettingPipeLine_;


	// CSParticle
	std::unique_ptr<CSParticlePipeLine> csParticlePipeLine_;

};

