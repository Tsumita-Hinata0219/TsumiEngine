#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>

// PSO
struct PsoProperty {
	ID3D12PipelineState* graphicsPipelineState = nullptr;
	ID3D12RootSignature* rootSignature = nullptr;
	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	D3D_PRIMITIVE_TOPOLOGY primitiveTopologyType;
};

// BlendMode
enum  BlendMode {
	None,
	Add,
	Subtruct,
	Multiply,
	Screen,
};

namespace PipeLine {
	
	// 第一層 : 大まかな対象
	enum class Container {
		None,

		Graphic,
		Compute,
	};

	// 第二層 : 対象の詳細カテゴリ
	enum class Category {
		None,

		Object2D,
		Object3D,
		SkinningObject3D,
		Skybox,

		CPUParticle,
		GPUParticle_Draw,

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

		GPUParticle_Init,
		CSParticle,
		Particle_EmitterSphere
	};

	// 第三層 : さらなる区分
	enum class SubFilter {
		None,

		Cull_Mode_Back,
		Cull_Mode_None,

		DepthWriteMask_Zero,

		Blend_Model_Normal,
		Blend_Model_Add,
		Blend_Model_Subtruct,
		Blend_Model_Multiply,
		Blend_Model_Screen,
	};
}
