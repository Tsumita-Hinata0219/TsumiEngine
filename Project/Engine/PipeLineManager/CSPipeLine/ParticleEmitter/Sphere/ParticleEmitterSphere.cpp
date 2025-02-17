#include "ParticleEmitterSphere.h"



// Psoを構築する
PsoProperty ParticleEmitterSphere::SetUpPso()
{
	/* --- RootSignatureを作成 --- */
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	SetUpRootSignature(descriptionRootSignature);


	/* --- Shaderを設定する --- */
	ShaderManager* shaderManager = ShaderManager::GetInstance();
	IDxcBlob* shaderBlob =
		shaderManager->GetComputeShader("GPUParticle_EmitterSphere").ComputeBlob; // shaderの取得
	D3D12_COMPUTE_PIPELINE_STATE_DESC computePipelineStateDesc{};
	computePipelineStateDesc.CS = {
		.pShaderBytecode = shaderBlob->GetBufferPointer(),
		.BytecodeLength = shaderBlob->GetBufferSize(),
	};
	computePipelineStateDesc.pRootSignature = pso_.rootSignature; // RootSignature


	// 実際に生成
	HRESULT hr{};
	hr = DirectXManager::GetInstance()->GetDevice()->CreateComputePipelineState(
		&computePipelineStateDesc, IID_PPV_ARGS(&pso_.graphicsPipelineState));

	return pso_;
}


// RootSignatureのセットアップ
void ParticleEmitterSphere::SetUpRootSignature(D3D12_ROOT_SIGNATURE_DESC& descriptionRootSignature)
{
	D3D12_ROOT_PARAMETER rootParameters[2]{};

	// u0 : Particleの要素
	D3D12_DESCRIPTOR_RANGE descriptorRange[1]{};
	descriptorRange[0].BaseShaderRegister = 0; // 0から始まる
	descriptorRange[0].NumDescriptors = 1; // 数は1つ
	descriptorRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	descriptorRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND; // offsetを自動計算
	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // ALLにする
	rootParameters[0].DescriptorTable.pDescriptorRanges = descriptorRange; // Tableの中身の配列を指定
	rootParameters[0].DescriptorTable.NumDescriptorRanges = _countof(descriptorRange); // Tableで利用する

	// b0 : Emitterの射出関連
	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV; // CBVを使う
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;// ComputeShaderで使う
	rootParameters[1].Descriptor.ShaderRegister = 0;// レジスタ番号


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
	hr_ = DirectXManager::GetInstance()->GetDevice()->CreateRootSignature(
		0,
		pso_.signatureBlob->GetBufferPointer(),
		pso_.signatureBlob->GetBufferSize(),
		IID_PPV_ARGS(&pso_.rootSignature));
	assert(SUCCEEDED(hr_));
}
