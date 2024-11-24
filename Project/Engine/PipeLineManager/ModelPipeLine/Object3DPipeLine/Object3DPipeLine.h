#pragma once

#include "../../IPipeLineState/IPipeLineState.h"


/* Object3DPipeLineクラス */
class Object3DPipeLine : public IPipeLineState {

public:

	/// <summary>
	/// PSOを構築する
	/// </summary>
	PsoProperty SetUpPso() override;


protected:

	/// <summary>
	/// RootSignatureのセットアップ
	/// </summary>
	void SetUpRootSignature(D3D12_ROOT_SIGNATURE_DESC& descriptionRootSignature) override;

};

