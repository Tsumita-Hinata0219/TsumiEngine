#pragma once

#include <d3dx12.h>
#include <dxcapi.h>

#include "MyMath.h"
#include "Struct.h"
#include "DirectXCommon.h"
#include "ShaderManager.h"
#include "GraphicPipelineStructure.h"


/* IPipeLineStateクラス */
class IPipeLineState {

public: // メンバ関数

	// Psoを構築する
	virtual void SetupLightPso() = 0;

	// RootSignatureのセットアップ
	virtual void SetUpRootSignature(D3D12_ROOT_SIGNATURE_DESC& descriptionRootSignature) = 0;

#pragma region Accessor アクセッサ

	// Psoの取得
	PsoProperty GetPsoProperty() const { return pso_; }

#pragma endregion


protected: // メンバ関数

	// InputLayoutのセットアップ
	void SetUpInputElementDescs(D3D12_INPUT_ELEMENT_DESC& inputElementDescs, LPCSTR SemanticName, UINT SemanticIndex, DXGI_FORMAT Format, UINT AlignedByteOffset);
	void SetUpInputLayout(D3D12_INPUT_LAYOUT_DESC& inputLayoutDesc, const D3D12_INPUT_ELEMENT_DESC* inputElementDescs, UINT numInputElements);

	// BlendStateのセットアップ
	void SetUpBlendState(D3D12_RENDER_TARGET_BLEND_DESC& blendDesc, BlendMode blendMode);

	// RasterizerStateのセットアップ
	void SetUpRasterizerState(D3D12_RASTERIZER_DESC& rasterizerDesc, D3D12_CULL_MODE Cull, D3D12_FILL_MODE fill);

	// Shadersのコンパイル
	void SetUpShader(IDxcBlob*& vertexShaderBlob, IDxcBlob*& pixelShaderBlob, ModelShaders type);
	void SetUpShader(IDxcBlob*& vertexShaderBlob, IDxcBlob*& pixelShaderBlob, PostEffectShaders type);

protected: // メンバ変数

	PsoProperty pso_{};

};

