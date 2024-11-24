#include "GPUParticleEmitterPipeLine.h"



// Psoを構築する
PsoProperty GPUParticleEmitterPipeLine::SetUpPso()
{
	/* --- RootSignatureを作成 --- */
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	SetUpRootSignature(descriptionRootSignature);


	/* --- Shaderを設定する --- */
	ShaderManager* shaderManager = ShaderManager::GetInstance();
	IDxcBlob* shaderBlob =
		shaderManager->GetComputeShader("GPUParticle_Sphere_Emitter").ComputeBlob; // shaderの取得
	D3D12_COMPUTE_PIPELINE_STATE_DESC computePipelineStateDesc{};
	computePipelineStateDesc.CS = {
		.pShaderBytecode = shaderBlob->GetBufferPointer(),
		.BytecodeLength = shaderBlob->GetBufferSize(),
	};
	computePipelineStateDesc.pRootSignature = pso_.rootSignature; // RootSignature


	// 実際に生成
	HRESULT hr{};
	hr = DirectXCommon::GetInstance()->GetDevice()->CreateComputePipelineState(
		&computePipelineStateDesc, IID_PPV_ARGS(&pso_.graphicsPipelineState));

	return pso_;
}


// RootSignatureのセットアップ
void GPUParticleEmitterPipeLine::SetUpRootSignature(D3D12_ROOT_SIGNATURE_DESC& descriptionRootSignature)
{

	D3D12_ROOT_PARAMETER rootParameters[4]{};
	// ─── CS
	// u0 : パーティクルパラメータ
	D3D12_DESCRIPTOR_RANGE parameterInstancing[1]{};
	parameterInstancing[0].BaseShaderRegister = 0; // 0から始まる
	parameterInstancing[0].NumDescriptors = 1; // 数は1つ
	parameterInstancing[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	parameterInstancing[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND; // offsetを自動計算
	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE; // DescriptorTableを使う
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // ALLで使う
	rootParameters[0].DescriptorTable.pDescriptorRanges = parameterInstancing; // Tableの中身の配列を指定
	rootParameters[0].DescriptorTable.NumDescriptorRanges = _countof(parameterInstancing); // Tableで利用する

	// u1 : FreeCounter
	D3D12_DESCRIPTOR_RANGE freeCounterRange[1]{};
	freeCounterRange[0].BaseShaderRegister = 1; // 0から始まる
	freeCounterRange[0].NumDescriptors = 1; // 数は1つ
	freeCounterRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	freeCounterRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND; // offsetを自動計算
	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // ALLにする
	rootParameters[1].DescriptorTable.pDescriptorRanges = freeCounterRange; // Tableの中身の配列を指定
	rootParameters[1].DescriptorTable.NumDescriptorRanges = _countof(freeCounterRange); // Tableで利用する

	// b0 : エミッター
	rootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV; // CBVを使う
	rootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // ALLで使う
	rootParameters[2].Descriptor.ShaderRegister = 0; // レジスタ番号

	// b1 :　PerFrame
	rootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV; // CBVを使う
	rootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // ALLで使う
	rootParameters[3].Descriptor.ShaderRegister = 1; // レジスタ番号


	descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_NONE; // コンピュートシェーダーに適用
	descriptionRootSignature.NumParameters = _countof(rootParameters); // rootParametersの数を設定
	descriptionRootSignature.pParameters = rootParameters; // パラメータを指定
	descriptionRootSignature.NumStaticSamplers = 0; // スタティックサンプラーがない場合
	descriptionRootSignature.pStaticSamplers = nullptr; // サンプラーも指定しない場合


	// シリアライズしてバイナリにする
	HRESULT hr_ = D3D12SerializeRootSignature(
		&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1,
		&pso_.signatureBlob,
		&pso_.errorBlob);
	if (FAILED(hr_)) {
		Log(reinterpret_cast<char*>(pso_.errorBlob->GetBufferPointer()));
		assert(false);
	}


	// バイナリを元に生成
	hr_ = DirectXCommon::GetInstance()->GetDevice()->CreateRootSignature(
		0,
		pso_.signatureBlob->GetBufferPointer(),
		pso_.signatureBlob->GetBufferSize(),
		IID_PPV_ARGS(&pso_.rootSignature));
	assert(SUCCEEDED(hr_));
}
