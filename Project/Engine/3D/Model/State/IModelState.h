#pragma once

#include "../../../BufferResource/BufferResource.h"
#include "../../../CommandManager/CommandManager.h"
#include "../../../View/SRVManager/SRVManager.h"
#include "../../../Transform/Transform.h"
#include "../../../PipeLineManager/PipeLineManager.h"
#include "../Structure/ModelStructure.h"
#include "../Resources/ModelResources.h"


enum StateType {
	NONE,
	OBJ,
	GLTF,
};
enum class CullingMode {
	None,
	Back,
};

// Modelの前方宣言
class Model;

// CameraManagerの前方宣言
class CameraManager;


/* ModelState モデルのステートパターン */
class IModelState {

public: // メンバ変数

	// デストラクタ
	virtual ~IModelState() {};

	// 描画処理
	virtual void Draw(Transform& transform) = 0;
	
	// コマンドコール
	virtual void CommandCall() = 0;

#pragma region Accessor アクセッサ

	// カリングモード
	void SetCullMode(const CullingMode& setMode) { this->cullMode_ = setMode; }

	// データのセット
	ModelDatas GetModelDatas() { return this->datas_; }
	void SetModelDatas(const ModelDatas& setData) { this->datas_ = setData; }
	
	// Mesh
	MeshData GetMeshData() const { return this->datas_.mesh; }
	void SetMeshData(const MeshData& setData) { this->datas_.mesh = setData; }

	// Material
	MaterialDataN GetMaterialData() const { return this->datas_.material; }
	void SetMaterialData(const MaterialDataN& seteData) { this->datas_.material = seteData; }
	// Color
	void SetMaterialColor(const Vector4& setColor) { this->datas_.material.color = setColor; }
	// Texture
	void SetMaterialTexture(uint32_t setTexture) { this->datas_.material.textureHandle = setTexture; }
	// uvTransform
	void SetMaterialUVMat(const Matrix4x4& setMat) { this->datas_.material.uvTransform = setMat; }

	// Light
	DirectionalLightData GetLightData() const { return this->datas_.light; }
	void SetLightData(const DirectionalLightData& setData) { this->datas_.light = setData; }

	// Environment
	EnvironmentData GetEnvironmentData() const { return this->datas_.environment; }
	void SetEnvironmentData(const EnvironmentData& setData) { this->datas_.environment = setData; }

	// ColorAddition
	ColorAddition GetColorAddition() const { return this->datas_.colorAddition; }
	void SetColorAddition(const ColorAddition& setData) { this->datas_.colorAddition = setData; }

#pragma endregion 


protected:

	// BufferResourceの生成
	void CreateBufferResource(ModelDatas datas) {
		// mesh
		buffers_.mesh.CreateResource(UINT(datas.mesh.vertices.size()));
		// vertexBufferView
		buffers_.vertex.CreateResource(UINT(datas.mesh.vertices.size()));
		buffers_.vertex.CreateVertexBufferView();
		// indexBufferView
		buffers_.indices.CreateResource(UINT(datas.mesh.indices.size()));
		buffers_.indices.CreateIndexBufferView();
		// transform
		buffers_.transform.CreateResource();
		// material
		buffers_.material.CreateResource();
		// light
		buffers_.light.CreateResource();
		// encironment
		buffers_.enviroment.CreateResource();
		// colorAddition
		buffers_.colorAddition.CreateResource();

		if (stateType_ == GLTF) {
			// influence
			buffers_.influence.CreateResource(UINT(datas.mesh.vertices.size()));
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

	// カリングモード
	CullingMode cullMode_ = CullingMode::Back;
};