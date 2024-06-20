#pragma once

#include "../../IPipeLineState/IPipeLineState.h"
#include "../../IPipeLineState/IPipeLine.h"


/* LambertPipeLineクラス */
class LambertPipeLine : public IPipeLine {

public:

	// Psoを構築する
	PsoProperty SetUpPso() override;


protected:

	// RootSignatureのセットアップ
	void SetUpRootSignature(D3D12_ROOT_SIGNATURE_DESC& descriptionRootSignature) override;

};

