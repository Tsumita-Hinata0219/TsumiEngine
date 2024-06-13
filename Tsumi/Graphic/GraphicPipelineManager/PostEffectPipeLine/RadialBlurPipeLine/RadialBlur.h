#pragma once

#include "IPipeLineState.h"

/* RadialBlurクラス */
class RadialBlur : public IPipeLineState {

public:

	// Psoを構築する
	void SetupLightPso() override;

	// RootSignatureのセットアップ
	void SetUpRootSignature(D3D12_ROOT_SIGNATURE_DESC& descriptionRootSignature) override;

};

