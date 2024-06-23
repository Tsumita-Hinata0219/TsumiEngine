#pragma once

#include "../../Base/WinApp/WinApp.h"
#include "../../CommandManager/CommandManager.h"
#include "../../../Project/Math/MyMath.h"
#include "../../CreateResource/CreateResource.h"
#include "../../DescriptorManager/DescriptorManager.h"
#include "../../PipeLineManager/PipeLineManager.h"
#include "../PostEffectMaterial/PostEffectMaterial.h"


/* IPostEffectクラス */
class IPostEffect {

public: // メンバ関数

	// コンストラクタ、デストラクタ
	IPostEffect() {};
	virtual ~IPostEffect() {};

	// 初期化処理、更新処理、描画処理
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;


protected: // メンバ関数

	// リソース作成
	void Create();

	// コマンドコール
	void CommandCall();


protected: // メンバ変数

	// マテリアル
	PostEffectMaterial material_;

	// SRV
	uint32_t srv_ = 0;

	// 座標
	Vector2 pos_{};

	// サイズ
	Vector2 size_ = { WinApp::kWindowWidth, WinApp::kWindowHeight };

};

