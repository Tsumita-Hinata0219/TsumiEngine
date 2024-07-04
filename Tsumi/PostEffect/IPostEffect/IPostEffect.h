#pragma once

#include "../../Base/WinApp/WinApp.h"
#include "../../BufferResource/BufferResource.h"
#include "../../CommandManager/CommandManager.h"
#include "../../../Project/Math/MyMath.h"
#include "../../CreateResource/CreateResource.h"
#include "../../DescriptorManager/DescriptorManager.h"
#include "../../PipeLineManager/PipeLineManager.h"
#include "../Materials/PostEffectMaterials.h"
#include "../PostEffectMaterial/PostEffectMaterial.h"
#include "../../Project/GameObject/Camera/Camera.h"


/* IPostEffectクラス */
class IPostEffect {

public: // メンバ関数

	// コンストラクタ、デストラクタ
	IPostEffect() {};
	virtual ~IPostEffect() {};

	// 初期化処理、更新処理、描画処理
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw(Camera* camera) = 0;

	// ImGuiの描画
	void DrawImGui();

public:

	enum class Type {
		None,
		BoxFilter,
		ColorGrading,
		Dissolve,
		GaussianFilter,
		Grain,
		GrayScale,
		OutLine,
		RadialBlur,
		Random,
		SepiaTone,
		Vignetting,
	};

protected: // メンバ関数

	// リソース作成
	void Create();

	// コマンドコール
	void CommandCall(Camera* camera);

	// PipeLineチェック
	void PipeLineCheck();


protected: // メンバ変数

	// マテリアル
	PostEffectMaterial material_;
	VignettingMaterial vignettingMtl_;

	// BoxFilter
	BoxFilterMtl boxFilterMtl_{};
	BufferResource<BoxFilterMtl> boxFilterBuffer_{};



	// SRV
	uint32_t srv_ = 0;

	// 座標
	Vector2 pos_{};

	// サイズ
	Vector2 size_ = { WinApp::kWindowWidth, WinApp::kWindowHeight };

	// PostEffectTyepe
	IPostEffect::Type effectType_ = IPostEffect::Type::None;

};

