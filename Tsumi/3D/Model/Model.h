#pragma once

#include "WorldTransform.h"
#include "ViewProjection.h"
#include "IModelState.h"
#include "ModelManager.h"
#include "ModelGLTFState.h"
#include "ModelObjState.h"
#include "ObjDataResource.h"
#include "ModelPlaneState.h"
#include "ModelSphereState.h"
#include "AnimationManager.h"
#include "KeyFrameAnimation.h"


/* Modelクラス */
class Model {

public: // メンバ関数

	Model() {};
	~Model() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(IModelState* state, WorldTransform worldTransform = { { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } });

	/// <summary>
	/// Objファイルの読み込み & Obj初期化処理
	/// </summary>
	void CreateFromObj(const std::string& routeFilePath, const std::string& fileName, WorldTransform worldTransform = { {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} });
	void CreateFromObjAssimpVer(const std::string& routeFilePath, const std::string& fileName, WorldTransform worldTransform = { {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} });
	void CreateGLTFModel(const std::string& routeFilePath, const std::string& fileName, const std::string& textureName, WorldTransform worldTransform = { {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} });

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(WorldTransform worldTransform, Camera* camera);

	/// <summary>
	/// Animationの再生
	/// </summary>
	void PlayAnimation(Animation animation, float time);

	/// <summary>
	/// Skeletonの更新処理
	/// </summary>
	void UpdateSkeleton(Skeleton& skeleton);

	/// <summary>
	/// Animationを適用する
	/// </summary>
	void ApplyAnimation(Skeleton& skeleton, const Animation& animation, float animationTime);


#pragma region Get

	// WorldTransform
	WorldTransform GetWorldTransform() { return this->worldTransform_; }

	// UseTexture
	uint32_t GetUseTexture() const { return this->useTexture_; }

	// NormalMapTexture
	uint32_t GetNormalMapTex() const { return this->normalMapTex_; }

	// Color
	Vector4 GetColor() const { return this->color_; }

	// DirectionalLight
	DirectionalLight GetDirectionalLight() const { return this->light_; }

	// SphereRadius
	float GetRadius() const { return this->radius_; }

	// fileName_
	const std::string GetObjFileName() { return this->fileName_; }

	// ObjHandle
	uint32_t GetObjHandle() const { return this->objHandle_; }

	// ObjData
	ModelData GetObjData() { return this->objData_; }

	// ライティングのタイプ
	ModelLightingType GetModelDrawType() const { return this->modelDrawType_; }

	// Node
	Node GetNode() const { return this->objData_.rootNode; }

#pragma endregion 


#pragma region Set

	// TextureHandle
	void SetTexHandle(uint32_t texHD) { this->useTexture_ = texHD; }

	// NormalMapTexture
	void SetNormalMapTex(uint32_t texHD) { this->normalMapTex_ = texHD; }

	// Color
	void SetColor(Vector4 color) { this->color_ = color; }

	// Light
	void SetDirectionalLight(DirectionalLight light) { this->light_ = light; }

	// DrawType
	void SetModelDrawType(ModelLightingType type) { this->modelDrawType_ = type; }

	// Node
	void SetNode(Node node) { this->objData_.rootNode = node; }

	// Node.localMatrix
	void SetNodeMatrix(Matrix4x4 setLocalMat) { this->objData_.rootNode.localMatrix = setLocalMat; }

#pragma endregion


private: // メンバ変数

	// ステートパターン
	IModelState* state_ = nullptr;

	// ワールド座標
	WorldTransform worldTransform_{};

	// テクスチャ
	uint32_t useTexture_{};
	uint32_t normalMapTex_{};

	// 色データ
	Vector4 color_{};

	// 光データ
	DirectionalLight light_{};

	// スフィアの半径
	float radius_ = 1.0f;

	// Objのファイルパス
	std::string fileName_{};
	std::string routeFilePath_{};

	// Objのハンドル
	uint32_t objHandle_{};

	ModelData modelData_{};

	ModelData objData_{};

	ModelLightingType modelDrawType_ = Non;

};