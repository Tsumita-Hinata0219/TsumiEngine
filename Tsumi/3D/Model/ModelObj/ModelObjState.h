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

#include <fstream>
#include <sstream>



/* ModelObjクラス */
class ModelObjState : public IModelState {

public: // メンバ関数

	ModelObjState() {};
	~ModelObjState() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(Model* pModel) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(Model* pModel, WorldTransform worldTransform, ViewProjection view) override;


private: // メンバ関数

	/// <summary>
	/// コマンドコール処理
	/// </summary>
	void CommandCall(uint32_t texture, WorldTransform worldTransform, ViewProjection view);

	/// <summary>
	/// objのファイルを読み込む
	/// </summary>
	ModelData LoadObjFile(Model* pModel, const std::string& directoryPath);

	/// <summary>
	/// mtlファイルを読み込む関数
	/// </summary>
	MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);


private: // メンバ関数

	// リソース
	ResourcePeroperty resource_{};

	// ModelData
	ModelData modelData_{};

	ObjData objData_{};
};