#pragma once

#ifndef BOXFILTEREFFECT_H
#define BOXFILTEREFFECT_H


#include "../../../BufferResource/BufferResource.h"
#include "../../../CommandManager/CommandManager.h"
#include "../../../PipeLineManager/PipeLineManager.h"
#include "../../../View/SRVManager/SRVManager.h"
#include "../../../View/RTVManager/RTVManager.h"
#include "../IPostEffect.h"
#include "../../Materials/PostEffectMaterials.h"


/* BoxFilterEffectクラス */
class BoxFilterEffect : public IPostEffect<BoxFilterMtl>{

public:

	// コンストラクタ、デストラクタ
	BoxFilterEffect() {};
	~BoxFilterEffect() {};

	// 初期化処理、描画処理
	void Initialize() override;
	void Draw([[maybe_unused]] Camera* camera) override;

	// Imguiの描画
	void DrawImGui(std::string name = "") override;


private:

	// コマンドコール
	void CommandCall() override;

//
//public:
//
//	// バッファーにセットするMaterialData
//	// 外部でも外部でも扱いやす用にpublicにしておく
//	BoxFilterMtl mtlData_{};
//
//
//private:
//
//	// SRV
//	uint32_t srv_ = 0;
//
//	// バッファー
//	BufferResource<BoxFilterMtl> mtlBuffer_{};
//
//	// ImGuiLabel 
//	std::string label_;
};

#endif // BOXFILTEREFFECT_H