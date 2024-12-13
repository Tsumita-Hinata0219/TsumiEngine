#pragma once

#include "../../BufferResource/BufferResource.h"
#include "../../CommandManager/CommandManager.h"
#include "../../DescriptorManager/DescriptorManager.h"
#include "../../Transform/WorldTransform/WorldTransform.h"
#include "../../Transform/Transform.h"
#include "../../PipeLineManager/PipeLineManager.h"
#include "IModelState.h"
#include "../../Animation/AnimationManager/AnimationManager.h"
#include "ModelStructure/ModelStructure.h"
#include "ModelResources/ModelResources.h"

#include "State/ModelState.h"
#include "State/OBJ/IOBJState.h"
#include "State/GLTF/IGLTFState.h"


// 前方宣言
class ModelManager;
class KeyFrameAnimation;
class CameraManager;
struct aiScene;


/* Modelクラス */
class Model {

public:

	// コンストラクタ、デストラクタ
	Model();
	Model(ModelDatas datas);
	~Model() {};
	
	// 描画処理
	void Draw(WorldTransform worldTransform);
	void AnimDraw(WorldTransform worldTransform, SkinCluster skinCluster);

	// 描画処理 <- new
	void DrawN(Transform& transform);

	// アニメーションの再生
	void PlayAnimation(Animation animation, float time);
	
	// スケルトンの生成
	Skeleton CreateSkeleton();

	// スケルトンの更新
	void UpdateSkeleton(Skeleton& skeleton);

	// アニメーション再生 <- 最新
	void ApplyAnimation(Skeleton& skeleton, const Animation& animation, float animationTime);

	// スキンクラスターの生成
	SkinCluster CreateSkinCluster(const Skeleton& skeleton);

	// スキンクラスターの更新
	void UpdateSkinCluster(SkinCluster& skinCluster, const Skeleton& skeleton);


#pragma region Accessor アクセッサ

	// ModelResourcesの取得
	ModelDatas GetModelResources() const { return this->modelState_->GetModelDatas(); }

	// Mesh
	MeshData GetMeshData() const { return this->modelState_->GetMeshData(); }
	void SetMeshData(const MeshData& setData) { this->modelState_->SetMeshData(setData); }

	// Material
	MaterialDataN GetMaterialData() const { return this->modelState_->GetMaterialData(); }
	void SetMaterialData(const MaterialDataN& seteData) { this->modelState_->SetMaterialData(seteData); }
	void SetMaterialColor(Vector4 color) { this->modelState_->SetMaterialColor(color); }
	void SetMaterialTexture(uint32_t setTexture) { this->modelState_->SetMaterialTexture(setTexture); }
	void SetMaterialUVMat(const Matrix4x4& setMat) { this->modelState_->SetMaterialUVMat(setMat); }

	// Light
	DirectionalLightData GetLightData() const { return this->modelState_->GetLightData(); }
	void SetLightData(const DirectionalLightData& setData) { this->modelState_->SetLightData(setData); }

	// Environment
	EnvironmentData GetEnvironmentData() const { return this->modelState_->GetEnvironmentData(); }
	void SetEnvironmentData(const EnvironmentData& setData) { this->modelState_->SetEnvironmentData(setData); }

	// ColorAddition
	ColorAddition GetColorAddition() const { return this->modelState_->GetColorAddition(); }
	void SetColorAddition(const ColorAddition& setData) { this->modelState_->SetColorAddition(setData); }


#pragma endregion 


private:

	// 繝｢繝・Ν繝槭ロ繝ｼ繧ｸ繝｣繝ｼ
	ModelManager* modelManager_ = nullptr;

	// 繧ｭ繝ｼ繝輔Ξ繝ｼ繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ
	KeyFrameAnimation* keyFrameAnimation_ = nullptr;

	// 繧ｹ繝・・繝医ヱ繧ｿ繝ｼ繝ｳ
	IModelState* state_ = nullptr;

	// 繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・
	WorldTransform worldTransform_{};

	// 繝・け繧ｹ繝√Ε
	uint32_t useTexture_{};
	uint32_t normalMapTex_{};

	// 濶ｲ繝・・繧ｿ
	Vector4 color_{};

	// 蜈峨ョ繝ｼ繧ｿ
	DirectionalLight light_{};

	// 繧ｹ繝輔ぅ繧｢縺ｮ蜊雁ｾ・
	float radius_ = 1.0f;

	// Obj縺ｮ繝輔ぃ繧､繝ｫ繝代せ
	std::string fileName_{};
	std::string routeFilePath_{};

	// Obj縺ｮ繝上Φ繝峨Ν
	uint32_t objHandle_{};

	ModelData modelData_{};

	ModelData objData_{};

	ModelLightingType modelDrawType_ = Non;




	// バッファーに書き込むデータ
	//ModelDatas datas_{};

	// バッファー
	//ModelBuffers buffers_{};

	// カメラマネージャー
	CameraManager* cameraManager_ = nullptr;

	// State
	ModelState* modelState_ = nullptr;
};