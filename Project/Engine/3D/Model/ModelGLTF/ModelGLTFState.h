#pragma once

#include "Base/DXCommon/DirectXCommon.h"
#include "CommandManager/CommandManager.h"
#include "Math/MyMath.h"
#include "Math/Struct.h"
#include "Transform/WorldTransform/WorldTransform.h"
#include "TextureManager/TextureManager.h"
#include "PipeLineManager/PipeLineManager.h"
#include "CreateResource/CreateResource.h"
#include "../IModelState.h"
#include "DescriptorManager/DescriptorManager.h"
#include "GameObject/Camera/Camera.h"

#include "GameObject/Camera/Manager/CameraManager.h"

#include <fstream>
#include <sstream>

class Model;

/* ModelGLTFクラス */
class ModelGLTFState : public IModelState {

public: // メンバ関数

	ModelGLTFState() { statetype_ = gLTF; };
	~ModelGLTFState() {};


	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(Model* pModel) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(Model* pModel, WorldTransform worldTransform) override;
	void AnimDraw(Model* pModel, WorldTransform worldTransform, SkinCluster skinCluster) override;


private: // メンバ関数

	/// <summary>
	/// コマンドコール処理
	/// </summary>
	void CommandCall(Model* pModel, WorldTransform worldTransform);
	void AnimCommandCall(Model* pModel, WorldTransform worldTransform, SkinCluster skinCluster);

private: // メンバ関数

	// リソース
	ResourcePeroperty resource_{};

	// ModelData
	ModelData modelData_{};

	// 
	uint32_t dsvIndex_ = 0;

};

