#pragma once

#include <iostream>

#include "../../Base/WinApp/WinApp.h"
#include "../../BufferResource/BufferResource.h"
#include "../../CommandManager/CommandManager.h"
#include "../../../Project/Math/MyMath.h"
#include "../../CreateResource/CreateResource.h"
#include "../../DescriptorManager/DescriptorManager.h"
#include "../../View/SRVManager/SRVManager.h"
#include "../../PipeLineManager/PipeLineManager.h"
#include "../Materials/PostEffectMaterials.h"
#include "../PostEffectMaterial/PostEffectMaterial.h"
#include "../../Project/GameObject/Camera/Camera.h"


/* IPostEffectクラス */
template <typename T>
class IPostEffect {

public: // メンバ関数

	// コンストラクタ、デストラクタ
	IPostEffect() {};
	virtual ~IPostEffect() {};

	// 初期化処理、更新処理、描画処理
	virtual void Initialize() = 0;
	virtual void Draw([[maybe_unused]] Camera* camera) = 0;

	// ImGuiの描画
	virtual void DrawImGui(std::string name = "") = 0;


protected:

	// コマンドコール
	virtual void CommandCall() = 0;


protected: // メンバ変数

	// SRV
	uint32_t srv_ = 0;

	// バッファーにセットするMaterialData
	T mtlData_{};

	// バッファー
	BufferResource<T> mtlBuffer_{};


	// ImGuiLabel 
	std::string label_;
};

