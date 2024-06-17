#pragma once

#include "MyMath.h"
#include "Struct.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "DirectXCommon.h"
#include "NormalGraphicPipeline.h"
#include "LightGraphicPipeline.h"
#include "CreateResource.h"
#include "IModelState.h"
#include "DescriptorManager.h"
#include "Camera.h"

#include <fstream>
#include <sstream>


/* ModelObjクラス */
class ModelObjState : public IModelState {

public: // メンバ関数

	ModelObjState() { statetype_ = Obj; };
	~ModelObjState() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(Model* pModel) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(Model* pModel, WorldTransform worldTransform, Camera* camera) override;
	void AnimDraw(Model* pModel, WorldTransform worldTransform, SkinCluster skinCluster, Camera* camera) override;


private: // メンバ関数

	/// <summary>
	/// コマンドコール処理
	/// </summary>
	void CommandCall(Model* pModel, WorldTransform worldTransform, Camera* camera);

private: // メンバ関数

	// リソース
	ResourcePeroperty resource_{};

	// ModelData
	ModelData modelData_{};
};