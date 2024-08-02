#pragma once

#include "../../../BufferResource/BufferResource.h"
#include "../../../CommandManager/CommandManager.h"
#include "../../../View/SRVManager/SRVManager.h"
#include "../../../Transform/Transform.h"
#include "../../../PipeLineManager/PipeLineManager.h"
#include "../ModelStructure/ModelStructure.h"
#include "../ModelResources/ModelResources.h"


enum StateType {
	NONE,
	OBJ,
	GLTF,
};


// Modelの前方宣言
class Model;

// CameraManagerの前方宣言
class CameraManager;


/* ModelState モデルのステートパターン */
class ModelState {

public: // メンバ変数

	// デストラクタ
	virtual ~ModelState() {};

	// 描画処理
	virtual void Draw(Transform transform) = 0;
	
	// コマンドコール
	virtual void CommandCall() = 0;

#pragma region Accessor アクセッサ

	// データのセット
	ModelDatas GetModelDatas() { return this->datas_; }
	void SetModelDatas(ModelDatas setData) { this->datas_ = setData; }
	
	// Mesh
	MeshData GetMeshData() const { return this->datas_.mesh; }
	void SetMeshData(MeshData setData) { this->datas_.mesh = setData; }

	// Material
	MaterialDataN GetMaterialData() const { return this->datas_.material; }
	void SetMaterialData(MaterialDataN seteData) { this->datas_.material = seteData; }

	// Light
	DirectionalLightData GetLightData() const { return this->datas_.light; }
	void SetLightData(DirectionalLightData setData) { this->datas_.light = setData; }

	// Environment
	EnvironmentData GetEnvironmentData() const { return this->datas_.environment; }
	void SetEnvironmentData(EnvironmentData setData) { this->datas_.environment = setData; }

#pragma endregion 


protected:

	// BufferResourceの生成
	void CreateBufferResource() {
		// mesh
		buffers_.mesh.CreateResource(UINT(datas_.mesh.vertices.size()));
		// vertexBufferView
		buffers_.vertex.CreateResource(UINT(datas_.mesh.vertices.size()));
		buffers_.vertex.CreateVertexBufferView();
		// indexBufferView
		buffers_.indeces.CreateResource(UINT(datas_.mesh.indices.size()));
		buffers_.indeces.CreateIndexBufferView();
		// material
		buffers_.material.CreateResource();
		// transform
		buffers_.transform.CreateResource();
		// light
		buffers_.light.CreateResource();
		// encironment
		buffers_.enviroment.CreateResource();

		if (stateType_ == GLTF) {
			// influence
			buffers_.influence.CreateResource(UINT(datas_.mesh.vertices.size()));
			// palette
			//buffers_.palette.CreateResource(UINT(datas_.skeleton.joints.size()));
		}
	}


protected: // メンバ変数

	// バッファーに書き込むデータ
	ModelDatas datas_{};

	// バッファー
	ModelBuffers buffers_{};

	// カメラマネージャー
	CameraManager* cameraManager_ = nullptr;

	// モデルステート
	StateType stateType_ = NONE;
};