#pragma once

#include "IPipeLineState.h"

/* RandomPipeLineクラス */
class RandomPipeLine : public IPipeLineState {

public:

	// Psoを構築する
	void SetupLightPso() override;

	// RootSignatureのセットアップ
	void SetUpRootSignature(D3D12_ROOT_SIGNATURE_DESC& descriptionRootSignature) override;

};

