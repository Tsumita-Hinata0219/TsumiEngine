#pragma once

#include "../../IPipeLineState/IPipeLineState.h"


/* Object3DPipeLineクラス */
class Object3DPipeLine : public IPipeLineState {

public:

	/// <summary>
	/// PSOを構築する
	/// </summary>
	PsoProperty SetUpPso() override;

#pragma region Accessor アクセッサ

	// CullModeの設定
	void SetCUllMode(const D3D12_CULL_MODE& setMode) { this->cullMode_ = setMode; }

#pragma endregion 


protected:

	/// <summary>
	/// RootSignatureのセットアップ
	/// </summary>
	void SetUpRootSignature(D3D12_ROOT_SIGNATURE_DESC& descriptionRootSignature) override;


private:

	// Cull_Mode
	D3D12_CULL_MODE cullMode_ = D3D12_CULL_MODE_BACK;

};

