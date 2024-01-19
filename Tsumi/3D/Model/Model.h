#pragma once

#include "WorldTransform.h"
#include "ViewProjection.h"
#include "IModelState.h"
#include "ModelManager.h"
#include "ModelObjState.h"
#include "ObjDataResource.h"
#include "ModelPlaneState.h"
#include "ModelSphereState.h"


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
	void CreateFromObj(const std::string& directoryPath, WorldTransform worldTransform = { { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } });

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(WorldTransform worldTransform, ViewProjection view);


#pragma region Get

	// WorldTransform
	WorldTransform GetWorldTransform() { return this->worldTransform_; }

	// UseTexture
	uint32_t GetUseTexture() { return this->useTexture_; }

	// Color
	Vector4 GetColor() { return this->color_; }

	// DirectionalLight
	DirectionalLight GetDirectionalLight() { return this->light_; }

	// SphereEnableLighting
	uint32_t GetEnableLighting() { return this->enableLighting_; }

	// SphereRadius
	float GetRadius() { return this->radius_; }

	// DirectoryPath
	const std::string GetObjDirectoryPath() { return this->directoryPath_; }

	// ObjHandle
	uint32_t GetObjHandle() { return objHandle_; }

	ObjData GetObjData() { return objData_; }

#pragma endregion 


#pragma region Set

	// TextureHandle
	void SetTexHandle(uint32_t texHD) { this->useTexture_ = texHD; }

	// Color
	void SetColor(Vector4 color) { this->color_ = color; }

#pragma endregion 


private: // メンバ関数



private: // メンバ変数

	// ステートパターン
	IModelState* state_ = nullptr;

	// ワールド座標
	WorldTransform worldTransform_{};

	// テクスチャ
	uint32_t useTexture_;

	// 色データ
	Vector4 color_{};

	// 光データ
	DirectionalLight light_;

	// スフィアのマテリアル
	uint32_t enableLighting_;

	// スフィアの半径
	float radius_ = 1.0f;

	// Objのファイルパス
	std::string directoryPath_{};

	// Objのハンドル
	uint32_t objHandle_;

	ModelData modelData_{};

	ObjData objData_{};

};