#pragma once


#include <d3dx12.h>
#include <dxcapi.h>

#include "../../../../Project/Math/MyMath.h"
#include "../../../../Project/Math/Struct.h"
#include "../../../Base/DXCommon/DirectXCommon.h"
#include "../../../ShaderManager/ShaderManager.h"
#include "../GraphicPipelineStructure.h"


class Object3DGraphicPipeLine {

private: // シングルトンパターン

	// コンストラクタ、デストラクタ
	Object3DGraphicPipeLine() = default;
	~Object3DGraphicPipeLine() = default;
	Object3DGraphicPipeLine(const Object3DGraphicPipeLine&) = delete;
	const Object3DGraphicPipeLine& operator=(const Object3DGraphicPipeLine&) = delete;

public: // メンバ関数

	/// <summary>
	/// NormalGraphicPipelineクラスのインスタンス取得
	/// </summary>
	static Object3DGraphicPipeLine* GetInstance() {
		static Object3DGraphicPipeLine instance;
		return &instance;
	}

	/// <summary>
	/// 初期化処理
	/// </summary>
	static void Initialize();

	/// <summary>
	/// PSOを構築する
	/// </summary>
	static void SetupObject3DPso();

	/// <summary>
	/// ModelPSOの取得
	/// </summary>
	static PsoProperty GetPsoProperty() { return Object3DGraphicPipeLine::GetInstance()->object3dPso_; }


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

	PsoProperty object3dPso_;
};

