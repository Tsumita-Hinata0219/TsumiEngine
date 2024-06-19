#include "IPipeLineState.h"
#include "../../ShaderManager/ShaderManager.h"




// InputLayoutのセットアップ
void IPipeLineState::SetUpInputElementDescs(D3D12_INPUT_ELEMENT_DESC& inputElementDescs, LPCSTR SemanticName, UINT SemanticIndex, DXGI_FORMAT Format, UINT AlignedByteOffset)
{
	inputElementDescs.SemanticName = SemanticName;
	inputElementDescs.SemanticIndex = SemanticIndex;
	inputElementDescs.Format = Format;
	inputElementDescs.AlignedByteOffset = AlignedByteOffset;
}
void IPipeLineState::SetUpInputLayout(D3D12_INPUT_LAYOUT_DESC& inputLayoutDesc, const D3D12_INPUT_ELEMENT_DESC* inputElementDescs, UINT numInputElements)
{
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = numInputElements;
}


// BlendStateのセットアップ
void IPipeLineState::SetUpBlendState(D3D12_RENDER_TARGET_BLEND_DESC& blendDesc, BlendMode blendMode)
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
void IPipeLineState::SetUpRasterizerState(D3D12_RASTERIZER_DESC& rasterizerDesc, D3D12_CULL_MODE Cull, D3D12_FILL_MODE fill)
{
	// 裏面(時計回り)を表示しない
	rasterizerDesc.CullMode = Cull;
	// 三角形の中を塗りつぶす
	rasterizerDesc.FillMode = fill;
}


// Shadersのコンパイル
void IPipeLineState::SetUpModelShader(IDxcBlob*& vertexShaderBlob, IDxcBlob*& pixelShaderBlob, ShaderManager::ModelShaders type)
{
	vertexShaderBlob = ShaderManager::GetInstance()->GetShader(type).VertexBlob;
	assert(vertexShaderBlob != nullptr);

	pixelShaderBlob = ShaderManager::GetInstance()->GetShader(type).PixelBlob;
	assert(pixelShaderBlob != nullptr);
}
void IPipeLineState::SetUpPostEffectShader(IDxcBlob*& vertexShaderBlob, IDxcBlob*& pixelShaderBlob, ShaderManager::PostEffectShaders type)
{
	vertexShaderBlob = ShaderManager::GetInstance()->GetShader(type).VertexBlob;
	assert(vertexShaderBlob != nullptr);

	pixelShaderBlob = ShaderManager::GetInstance()->GetShader(type).PixelBlob;
	assert(pixelShaderBlob != nullptr);
}

