#include "SkinningObject3dGraphicPipeLine.h"



// SkinningObject3dクラスのインスタンス取得
SkinningObject3dGraphicPipeLine* SkinningObject3dGraphicPipeLine::GetInstance()
{
	static SkinningObject3dGraphicPipeLine instance;
	return &instance;
}


// 初期化処理
void SkinningObject3dGraphicPipeLine::Initialize()
{



}


// PSOを構築する
void SkinningObject3dGraphicPipeLine::SetUpSkinningObject3dPso()
{
	SkinningObject3dGraphicPipeLine* skinningObject3dGraphicPipeline = SkinningObject3dGraphicPipeLine::GetInstance();


	/* --- RootSignatureを作成 --- */
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	skinningObject3dGraphicPipeline->SetupRootSignature(descriptionRootSignature);


	/* --- InputLayoutを設定する --- */
	std::array<D3D12_INPUT_ELEMENT_DESC, 7> inputElementDescs{};
	skinningObject3dGraphicPipeline->SetInputElementDescs(inputElementDescs);

	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	skinningObject3dGraphicPipeline->SetInputLayout(inputLayoutDesc, inputElementDescs);


	/* --- BlendStateを設定する --- */
	// 全ての色要素を書き込む
	D3D12_BLEND_DESC blendDesc{};
	D3D12_RENDER_TARGET_BLEND_DESC& pBlendDesc = blendDesc.RenderTarget[0];
	skinningObject3dGraphicPipeline->SetupBlendState(pBlendDesc, BlendNone);


	/* --- RasiterzerStateを設定する --- */
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	skinningObject3dGraphicPipeline->SetupRasterizerState(rasterizerDesc);


	/* --- Shaderをcompileする --- */
	// Shaderをコンパイルする
	IDxcBlob* vertexShaderBlob = nullptr;
	IDxcBlob* pixelShaderBlob = nullptr;
	skinningObject3dGraphicPipeline->CompileShaders(vertexShaderBlob, pixelShaderBlob);


	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};

	graphicsPipelineStateDesc.pRootSignature = SkinningObject3dGraphicPipeLine::GetInstance()->skinningObject3dPso_.rootSignature; // RootSignature

	graphicsPipelineStateDesc.InputLayout = inputLayoutDesc; // InputLayout

	graphicsPipelineStateDesc.BlendState = blendDesc; // BlendState

	graphicsPipelineStateDesc.RasterizerState = rasterizerDesc; // RasterizeState

	graphicsPipelineStateDesc.VS = {
		vertexShaderBlob->GetBufferPointer(),
		vertexShaderBlob->GetBufferSize() }; // VertexShader

	graphicsPipelineStateDesc.PS = {
		pixelShaderBlob->GetBufferPointer(),
		pixelShaderBlob->GetBufferSize() }; // PixelShader


	// 書き込むRTVの情報
	graphicsPipelineStateDesc.NumRenderTargets = 1;
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;


	// 利用するトポロジ(形状)もタイプ。三角形
	graphicsPipelineStateDesc.PrimitiveTopologyType =
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;


	// どのように画面に色を打ち込むかの設定(気にしなくて良い)
	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	D3D12_DEPTH_STENCIL_DESC depthStencilDesc{};
	// Depthの機能を有効化する
	depthStencilDesc.DepthEnable = true;
	// 書き込む
	depthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	// 比較関数はLessEqual。つまり、近ければ描画される
	depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;

	// DepthStencilの設定
	graphicsPipelineStateDesc.DepthStencilState = depthStencilDesc;
	graphicsPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;


	// 実際に生成
	HRESULT hr{};
	hr = DirectXCommon::GetInstance()->GetDevice()->CreateGraphicsPipelineState(
		&graphicsPipelineStateDesc,
		IID_PPV_ARGS(&SkinningObject3dGraphicPipeLine::GetInstance()->skinningObject3dPso_.graphicsPipelineState));
	assert(SUCCEEDED(hr));
}



// RootSignatureのセットアップ
void SkinningObject3dGraphicPipeLine::SetupRootSignature(D3D12_ROOT_SIGNATURE_DESC& descriptionRootSignature)
{
	descriptionRootSignature.Flags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;


	// 色に関する
	D3D12_ROOT_PARAMETER rootParameters[6]{};
	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV; // CBVを使う
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixelShaderで使う
	rootParameters[0].Descriptor.ShaderRegister = 0; // レジスタ番号0とバインド


	// 頂点位置に関する
	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV; // CBVを使う
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;// VertexShaderで使う
	rootParameters[1].Descriptor.ShaderRegister = 0;// レジスタ番号を0にバインド

	descriptionRootSignature.pParameters = rootParameters; // ルートパラメータ配列へのポインタ
	descriptionRootSignature.NumParameters = _countof(rootParameters); // 配列の長さ


	// Viewに関する
	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[2].Descriptor.ShaderRegister = 1;


	// テクスチャに関する
	D3D12_DESCRIPTOR_RANGE descriptorRange[1]{};
	descriptorRange[0].BaseShaderRegister = 0; // 0から始まる
	descriptorRange[0].NumDescriptors = 1; // 数は1つ
	descriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND; // offsetを自動計算

	rootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; // DescriptorTableを使う
	rootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixShaderで使う
	rootParameters[3].DescriptorTable.pDescriptorRanges = descriptorRange; // Tableの中身の配列を指定
	rootParameters[3].DescriptorTable.NumDescriptorRanges = _countof(descriptorRange); // Tableで利用する


	// 光に関する
	rootParameters[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV; // CBVを使う
	rootParameters[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixelShaderで使う
	rootParameters[4].Descriptor.ShaderRegister = 1; // レジスタ番号0とバインド


	// Samplerの設定
	D3D12_STATIC_SAMPLER_DESC staticSamplers[1]{};
	staticSamplers[0].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR; // バイリニアフィルタ
	staticSamplers[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 0～1の範囲外をリピート
	staticSamplers[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;

	staticSamplers[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER; // 比較しない
	staticSamplers[0].MaxLOD = D3D12_FLOAT32_MAX; // ありったけのMipmapを使う
	staticSamplers[0].ShaderRegister = 0; // レジスタ番号0を使う
	staticSamplers[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // PixelShaderで使う

	descriptionRootSignature.pStaticSamplers = staticSamplers;
	descriptionRootSignature.NumStaticSamplers = _countof(staticSamplers);


	// MatrixPaletteに関する
	D3D12_DESCRIPTOR_RANGE descriptorRangeForInstancing[1] = {};
	descriptorRangeForInstancing[0].BaseShaderRegister = 0;
	descriptorRangeForInstancing[0].NumDescriptors = 1;
	descriptorRangeForInstancing[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRangeForInstancing[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	rootParameters[5].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[5].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[5].DescriptorTable.pDescriptorRanges = descriptorRangeForInstancing;
	rootParameters[5].DescriptorTable.NumDescriptorRanges = _countof(descriptorRangeForInstancing); 


	// シリアライズしてバイナリにする
	HRESULT hr_ = D3D12SerializeRootSignature(
		&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1,
		&SkinningObject3dGraphicPipeLine::GetInstance()->skinningObject3dPso_.signatureBlob,
		&SkinningObject3dGraphicPipeLine::GetInstance()->skinningObject3dPso_.errorBlob);
	if (FAILED(hr_)) {
		Log(reinterpret_cast<char*>(SkinningObject3dGraphicPipeLine::GetInstance()->skinningObject3dPso_.errorBlob->GetBufferPointer()));
		assert(false);
	}


	// バイナリを元に生成
	hr_ = DirectXCommon::GetInstance()->GetDevice()->CreateRootSignature(
		0,
		SkinningObject3dGraphicPipeLine::GetInstance()->skinningObject3dPso_.signatureBlob->GetBufferPointer(),
		SkinningObject3dGraphicPipeLine::GetInstance()->skinningObject3dPso_.signatureBlob->GetBufferSize(),
		IID_PPV_ARGS(&SkinningObject3dGraphicPipeLine::GetInstance()->skinningObject3dPso_.rootSignature));
	assert(SUCCEEDED(hr_));
}


// InputLayoutのセットアップ
void SkinningObject3dGraphicPipeLine::SetupInputElementDescs(D3D12_INPUT_ELEMENT_DESC& inputElementDescs, LPCSTR SemanticName, UINT SemanticIndex, DXGI_FORMAT Format, UINT AlignedByteOffset)
{
	inputElementDescs.SemanticName = SemanticName;
	inputElementDescs.SemanticIndex = SemanticIndex;
	inputElementDescs.Format = Format;
	inputElementDescs.AlignedByteOffset = AlignedByteOffset;
}
void SkinningObject3dGraphicPipeLine::SetupInputLayout(D3D12_INPUT_LAYOUT_DESC& inputLayoutDesc, const D3D12_INPUT_ELEMENT_DESC* inputElementDescs, UINT numInputElements)
{
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = numInputElements;
}
void SkinningObject3dGraphicPipeLine::SetInputElementDescs(std::array<D3D12_INPUT_ELEMENT_DESC, 7>& inputElementDescs)
{
	// POSITION
	inputElementDescs[0].SemanticName = "POSITION";
	inputElementDescs[0].SemanticIndex = 0;
	inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

	// TEXCOORD
	inputElementDescs[1].SemanticName = "TEXCOORD";
	inputElementDescs[1].SemanticIndex = 0;
	inputElementDescs[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	inputElementDescs[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

	// NORMAL
	inputElementDescs[2].SemanticName = "NORMAL";
	inputElementDescs[2].SemanticIndex = 0;
	inputElementDescs[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	inputElementDescs[2].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

	// WORLDPOSITION
	inputElementDescs[3].SemanticName = "WORLDPOSITION";
	inputElementDescs[3].SemanticIndex = 0;
	inputElementDescs[3].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	inputElementDescs[3].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

	// CAMERAPOSITION
	inputElementDescs[4].SemanticName = "CAMERAPOSITION";
	inputElementDescs[4].SemanticIndex = 0;
	inputElementDescs[4].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	inputElementDescs[4].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

	// WEIGHT
	inputElementDescs[5].SemanticName = "WEIGHT";
	inputElementDescs[5].SemanticIndex = 0;
	inputElementDescs[5].Format = DXGI_FORMAT_R32G32B32A32_FLOAT; // float32_t4
	inputElementDescs[5].InputSlot = 1; // 1番目のslotのVBVのことだと伝える
	inputElementDescs[5].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

	// INDEX
	inputElementDescs[6].SemanticName = "INDEX";
	inputElementDescs[6].SemanticIndex = 0;
	inputElementDescs[6].Format = DXGI_FORMAT_R32G32B32A32_SINT; // int32_t4
	inputElementDescs[6].InputSlot = 1; // 1番目のslotのVBVのことだと伝える
	inputElementDescs[6].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
}
void SkinningObject3dGraphicPipeLine::SetInputLayout(D3D12_INPUT_LAYOUT_DESC& inputLayoutDesc, const std::array<D3D12_INPUT_ELEMENT_DESC, 7>& inputElementDescs)
{
	inputLayoutDesc.pInputElementDescs = inputElementDescs.data();
	inputLayoutDesc.NumElements = static_cast<UINT>(inputElementDescs.size());
}


// BlendStateのセットアップ
void SkinningObject3dGraphicPipeLine::SetupBlendState(D3D12_RENDER_TARGET_BLEND_DESC& blendDesc, BlendMode blendMode)
{
	blendDesc.RenderTargetWriteMask =
		D3D12_COLOR_WRITE_ENABLE_ALL;
	blendDesc.BlendEnable = true;


	switch (blendMode)
	{
	case BlendNone:
		blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
		blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;
		blendDesc.DestBlendAlpha = D3D12_BLEND_ZERO;
		blendDesc.BlendOp = D3D12_BLEND_OP_ADD;
		blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
		blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
		break;

	case BlendAdd:
		blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
		blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;
		blendDesc.DestBlendAlpha = D3D12_BLEND_ZERO;
		blendDesc.BlendOp = D3D12_BLEND_OP_ADD;
		blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
		blendDesc.DestBlend = D3D12_BLEND_ONE;
		break;

	case BlendSubtruct:
		blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
		blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;
		blendDesc.DestBlendAlpha = D3D12_BLEND_ZERO;
		blendDesc.BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;
		blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
		blendDesc.DestBlend = D3D12_BLEND_ONE;
		break;

	case BlendMultiply:
		blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
		blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;
		blendDesc.DestBlendAlpha = D3D12_BLEND_ZERO;
		blendDesc.BlendOp = D3D12_BLEND_OP_ADD;
		blendDesc.SrcBlend = D3D12_BLEND_ZERO;
		blendDesc.DestBlend = D3D12_BLEND_SRC_COLOR;
		break;

	case BlendScreen:
		blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
		blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;
		blendDesc.DestBlendAlpha = D3D12_BLEND_ZERO;
		blendDesc.BlendOp = D3D12_BLEND_OP_ADD;
		blendDesc.SrcBlend = D3D12_BLEND_INV_DEST_COLOR;
		blendDesc.DestBlend = D3D12_BLEND_ONE;
		break;

	default:
		break;
	}
}


// RasterizerStateのセットアップ
void SkinningObject3dGraphicPipeLine::SetupRasterizerState(D3D12_RASTERIZER_DESC& rasterizerDesc)
{
	// 裏面(時計回り)を表示しない
	rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	// 三角形の中を塗りつぶす
	rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
}


// Shadersのコンパイル
void SkinningObject3dGraphicPipeLine::CompileShaders(IDxcBlob*& vertexShaderBlob, IDxcBlob*& pixelShaderBlob)
{
	vertexShaderBlob = ShaderManager::GetInstance()->GetShaderType().skinningObject3d.VertexBlob;
	assert(vertexShaderBlob != nullptr);

	pixelShaderBlob = ShaderManager::GetInstance()->GetShaderType().skinningObject3d.PixelBlob;
	assert(pixelShaderBlob != nullptr);
}
