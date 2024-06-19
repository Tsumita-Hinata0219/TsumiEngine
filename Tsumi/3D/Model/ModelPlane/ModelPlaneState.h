#pragma once

#include "../Base/DXCommon/DirectXCommon.h"
#include "../CommandManager/CommandManager.h"
#include "../TextureManager/TextureManager.h"
#include "../Graphic/GraphicPipelineManager/Normal/NormalGraphicPipeline.h"
#include "../CreateResource/CreateResource.h"
#include "../DescriptorManager/DescriptorManager.h"
#include "../IModelState.h"
#include "../Transform/WorldTransform/WorldTransform.h"
#include "../Project/Math/MyMath.h"
#include "../Project/Math/Struct.h"
#include "../../../Project/GameObject/Camera/Camera.h"


/* ModelPlaneクラス */
class ModelPlaneState : public IModelState {

public: // メンバ関数

	ModelPlaneState() { statetype_ = Normal; };
	~ModelPlaneState() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(Model* pModel) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(Model* pModel, WorldTransform worldTransform, Camera* camera) override;


private: // メンバ関数

	/// <summary>
	/// コマンドコール処理
	/// </summary>
	void CommandCall(uint32_t texture, WorldTransform worldTransform, Camera* camera);


private: // メンバ関数

	// リソース
	ResourcePeroperty resource_{};

	// サイズ
	float size_;
};