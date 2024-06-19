#pragma once

#include "../../ShaderManager/ShaderManager.h"

#include <d3dx12.h>
#include <dxcapi.h>

#include "../Project/Math/MyMath.h"
#include "../Project/Math/Struct.h"
#include "../Base/DXCommon/DirectXCommon.h"
#include "../GraphicPipelineStructure.h"

// PipeLineType
enum class IPipeLineType {
	Lambert,
	Light,
	Line,
	Normal,
	Object3D,
	Particle,
	PhongNormalMap,
	Phong,
	Sprite,
	BoxFilter,
	Dissolve,
	GaussianFilter,
	GrayScale,
	OutLine,
	RadialBlur,
	Random,
	SepiaTone,
	Vignetting,
	Count,
};


/* IPipeLineStateクラス */
class IPipeLineState {

public: // メンバ関数

	// Psoを構築する
	virtual PsoProperty SetUpPso() = 0;

#pragma region Accessor アクセッサ

	// Psoの取得
	PsoProperty GetPsoProperty() const { return pso_; }

#pragma endregion


private: // メンバ関数

	// RootSignatureのセットアップ
	virtual void SetUpRootSignature(D3D12_ROOT_SIGNATURE_DESC& descriptionRootSignature) = 0;


protected: // メンバ関数

	// InputLayoutのセットアップ
	void SetUpInputElementDescs(D3D12_INPUT_ELEMENT_DESC& inputElementDescs, LPCSTR SemanticName, UINT SemanticIndex, DXGI_FORMAT Format, UINT AlignedByteOffset);
	void SetUpInputLayout(D3D12_INPUT_LAYOUT_DESC& inputLayoutDesc, const D3D12_INPUT_ELEMENT_DESC* inputElementDescs, UINT numInputElements);

	// BlendStateのセットアップ
	void SetUpBlendState(D3D12_RENDER_TARGET_BLEND_DESC& blendDesc, BlendMode blendMode);

	// RasterizerStateのセットアップ
	void SetUpRasterizerState(D3D12_RASTERIZER_DESC& rasterizerDesc, D3D12_CULL_MODE Cull, D3D12_FILL_MODE fill);

	// Shadersのコンパイル
	void SetUpModelShader(IDxcBlob*& vertexShaderBlob, IDxcBlob*& pixelShaderBlob, ShaderManager::ModelShaders type);
	void SetUpPostEffectShader(IDxcBlob*& vertexShaderBlob, IDxcBlob*& pixelShaderBlob, ShaderManager::PostEffectShaders type);


protected: // メンバ変数

	PsoProperty pso_{};

};

