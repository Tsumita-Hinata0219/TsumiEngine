#pragma once

#include <d3dx12.h>
#include <dxcapi.h>

#include "MyMath.h"
#include "Struct.h"
#include "DirectXCommon.h"
#include "ShaderManager.h"
#include "GraphicPipelineStructure.h"


/* IPipeLineStateクラス */
class IPipeLineState {

public: // メンバ関数

	// Psoを構築する
	virtual void SetupLightPso() = 0;

	// Psoの取得
	PsoProperty GetPsoProperty() const { return pso_; }


protected: // メンバ関数


protected: // メンバ変数

	PsoProperty pso_{};

};

