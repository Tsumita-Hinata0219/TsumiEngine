#pragma once

#include "../../../BufferResource/BufferResource.h"
#include "../../../CommandManager/CommandManager.h"
#include "../../../CreateResource/CreateResource.h"
#include "../../../PipeLineManager/PipeLineManager.h"
#include "../../../View/SRVManager/SRVManager.h"
#include "../../../View/RTVManager/RTVManager.h"
#include "../../Materials/PostEffectMaterials.h"
#include "../../PostEffectMaterial/PostEffectMaterial.h"


/* BoxFilterEffectクラス */
class BoxFilterEffect {

public:

	// コンストラクタ、デストラクタ
	BoxFilterEffect() {};
	~BoxFilterEffect() {};

	// 初期化処理、描画処理
	void Initialize();
	void Draw();

	// Imguiの描画
	void DrawImGui(std::string name = "");


public:

	// バッファーにセットするMaterialData
	// 外部でも外部でも扱いやす用にpublicにしておく
	BoxFilterMtl mtlData_{};


private:

	// SRV
	uint32_t srv_ = 0;

	// バッファー
	BufferResource<BoxFilterMtl> mtlBuffer_{};

	// string 
	std::string label_;

};

