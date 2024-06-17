#pragma once

#include <d3dx12.h>
#include <dxcapi.h>

#include "MyMath.h"
#include "Struct.h"
#include "DirectXCommon.h"
#include "ShaderManager.h"
#include "GraphicPipelineStructure.h"


class SkinningObject3dGraphicPipeLine
{

public: // メンバ関数

	/// <summary>
	/// PhongGraphicPipelineクラスのインスタンス取得
	/// </summary>
	static SkinningObject3dGraphicPipeLine* GetInstance();

	/// <summary>
	/// 初期化処理
	/// </summary>
	static void Initialize();

	/// <summary>
	/// PSOを構築する
	/// </summary>
	static void SetUpSkinningObject3dPso();

	/// <summary>
	/// phongPSOの取得
	/// </summary>
	static PsoProperty GetPsoProperty() { return SkinningObject3dGraphicPipeLine::GetInstance()->skinningObject3dPso_; }


private:

	/// <summary>
	/// RootSignatureのセットアップ
	/// </summary>
	void SetupRootSignature(D3D12_ROOT_SIGNATURE_DESC& descriptionRootSignature);

	/// <summary>
	/// InputLayoutのセットアップ
	/// </summary>
	void SetupInputElementDescs(D3D12_INPUT_ELEMENT_DESC& inputElementDescs, LPCSTR SemanticName, UINT SemanticIndex, DXGI_FORMAT Format, UINT AlignedByteOffset);
	void SetupInputLayout(D3D12_INPUT_LAYOUT_DESC& inputLayoutDesc, const D3D12_INPUT_ELEMENT_DESC* inputElementDescs, UINT numInputElements);
	void SetInputElementDescs(std::array<D3D12_INPUT_ELEMENT_DESC, 7>& inputElementDescs);
	void SetInputLayout(D3D12_INPUT_LAYOUT_DESC& inputLayoutDesc, const std::array<D3D12_INPUT_ELEMENT_DESC, 7>& inputElementDescs);
	
	/// <summary>
	/// BlendStateのセットアップ
	/// </summary>
	void SetupBlendState(D3D12_RENDER_TARGET_BLEND_DESC& blendDesc, BlendMode blendMode);

	/// <summary>
	/// RasterizerStateのセットアップ
	/// </summary>
	void SetupRasterizerState(D3D12_RASTERIZER_DESC& rasterizerDesc);

	/// <summary>
	/// Shadersのコンパイル
	/// </summary>
	void CompileShaders(IDxcBlob*& vertexShaderBlob, IDxcBlob*& pixelShaderBlob);


private: // メンバ変数

	PsoProperty skinningObject3dPso_{};

};
