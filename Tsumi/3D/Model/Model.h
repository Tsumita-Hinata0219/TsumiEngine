#pragma once

#include "WorldTransform.h"
#include "ViewProjection.h"
#include "IModelState.h"
#include "ModelGLTFState.h"
#include "ModelObjState.h"
#include "ObjDataResource.h"
#include "ModelPlaneState.h"
#include "ModelSphereState.h"
#include "AnimationManager.h"

#include "Transform.h"
#include "Mesh.h"
#include "Material.h"

#include "Node.h"
#include "Skeleton.h"


class ModelManager;
class KeyFrameAnimation;


//// モデルデータ
//struct ModelData {
//	std::map<string, JointWeightData> skinClusterData;
//	std::vector<VertexData> vertices;
//	std::vector<uint32_t> indices;
//	MaterialData material;
//	uint32_t textureHD;
//	Node rootNode;
//};
//// Objデータ
//struct ObjData {
//	uint32_t index;
//	vector<VertexData> vertices;
//	MaterialData material;
//	Node node;
//};


/* Modelクラス */
class Model {

public:

	// PipeLineのタイプ
	enum class PipeLineType : uint32_t {
		kNone,
		kModel,
		kParticle,
		kPostEffect,
	};

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Model();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Model() {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(IModelState* state, WorldTransform worldTransform = WorldTransform());

	/// <summary>
	/// Objファイルの読み込み & Obj初期化処理
	/// </summary>
	void CreateFromObj(const std::string& routeFilePath, const std::string& fileName, WorldTransform worldTransform = WorldTransform());
	void CreateFromObjAssimpVer(const std::string& routeFilePath, const std::string& fileName, WorldTransform worldTransform = WorldTransform());
	void CreateGLTFModel(const std::string& routeFilePath, const std::string& fileName, const std::string& textureName, WorldTransform worldTransform = WorldTransform());


	/// <summary>
	/// モデルの読み込み
	/// </summary>
	static unique_ptr<Model> LoadObjFileAssimpVer(const std::string& routeFilePath, const std::string& fileName);
	static unique_ptr<Model> LoadGLTF(const std::string& routeFilePath, const std::string& fileName, const std::string& textureName);

	/// <summary>
	/// PipeLineTypeの設定
	/// </summary>
	static void SetPipeLineType(const PipeLineType type);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(WorldTransform worldTransform, Camera* camera);
	void AnimDraw(WorldTransform worldTransform, SkinCluster skinCluster, Camera* camera);
	void DrawN(Transform transform, Camera* camera);

	/// <summary>
	/// Animationの再生
	/// </summary>
	void PlayAnimation(Animation animation, float time);

	/// <summary>
	/// Nodeの階層構造からSkeletonを作る
	/// </summary>
	Skeleton CreateSkeleton();

	/// <summary>
	/// Skeletonの更新処理
	/// </summary>
	void UpdateSkeleton(Skeleton& skeleton);

	/// <summary>
	/// Animationを適用する
	/// </summary>
	void ApplyAnimation(Skeleton& skeleton, const Animation& animation, float animationTime);


	/// <summary>
	/// SKinClusterの生成
	/// </summary>
	SkinCluster CreateSkinCluster(const Skeleton& skeleton);


	/// <summary>
	/// SkinCLusterの更新処理
	/// </summary>
	void UpdateSkinCluster(SkinCluster& skinCluster, const Skeleton& skeleton);

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


private:

	/// <summary>
	/// mtlファイルを読み込む関数
	/// </summary>
	MaterialModel* LoadMaterialTemplateFile(const std::string& filePath, const std::string& fileName);

	/// <summary>
	/// コマンドコール
	/// </summary>
	void CommandCall(Transform transform, Camera* camera);

private: // メンバ変数

	// モデルマネージャー
	ModelManager* modelManager_ = nullptr;

	// キーフレーアニメーション
	KeyFrameAnimation* keyFrameAnimation_ = nullptr;

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


	// ↓↓↓↓↓↓↓↓ こっから新しいモデル描画に必要な値

	// Modelの名前
	string name_;

	// Meshデータ
	unordered_map<string, unique_ptr<Mesh>> meshMap_;

	// Materialデータ
	unordered_map<string, unique_ptr<MaterialModel>> materialMap_;

	// PipeLineのタイプ
	static PipeLineType pipeLineType_;
};