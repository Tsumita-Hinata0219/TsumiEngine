#pragma once

#include "../../../Tsumi/Base/DXCommon/DirectXCommon.h"
#include "../../../Tsumi/CommandManager/CommandManager.h"
#include "../../../Tsumi/TextureManager/TextureManager.h"
#include "../../../Tsumi/PipeLineManager/PipeLineManager.h"
#include "../../../Tsumi/CreateResource/CreateResource.h"
#include "../../../Tsumi/DescriptorManager/DescriptorManager.h"
#include "../IModelState.h"
#include "../../../Tsumi/Transform/WorldTransform/WorldTransform.h"
#include "Math/MyMath.h"
#include "Math/Struct.h"
#include "GameObject/Camera/Manager/CameraManager.h"

#include <fstream>
#include <sstream>

class Model;

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
	void Draw(Model* pModel, WorldTransform worldTransform) override;
	void AnimDraw(Model* pModel, WorldTransform worldTransform, SkinCluster skinCluster) override;


private: // メンバ関数

	/// <summary>
	/// コマンドコール処理
	/// </summary>
	void CommandCall(Model* pModel, WorldTransform worldTransform);

private: // メンバ関数

	// リソース
	ResourcePeroperty resource_{};

	// ModelData
	ModelData modelData_{};
};