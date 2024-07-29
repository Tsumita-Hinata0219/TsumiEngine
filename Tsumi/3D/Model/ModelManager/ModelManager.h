#pragma once

#include "../../../../Project/Math/MyMath.h"
#include "../../../../Project/Math/Struct.h"
#include "../../../TextureManager/TextureManager.h"
#include "../ModelObj/ObjDataResource/ObjDataResource.h"
#include "../Model.h"

#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <filesystem>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>



namespace ModelFileFormat {
	const std::pair<std::string, uint32_t> OBJ = { ".obj", 0 };
	const std::pair<std::string, uint32_t> GLTF = { ".gltf", 1 };
}

struct aiScene;



/* ModelManagerクラス */
class ModelManager {

private: // シングルトンデザインパターン

	// コンストラクタ、デストラクタ
	ModelManager() = default;
	~ModelManager() = default;
	ModelManager(const ModelManager&) = delete;
	const ModelManager& operator=(const ModelManager&) = delete;

public: // メンバ関数

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	static ModelManager* GetInstance() {
		static ModelManager instance;
		return &instance;
	}

	/// <summary>
	/// 解放処理
	/// </summary>
	static void Finalize();

	/// <summary>
	/// モデルデータの取得
	/// </summary>
	std::unique_ptr<Model> GetModel(const std::string& name) const;

	/// <summary>
	/// 指定のモデルデータの破棄
	/// </summary>
	void ModelRemove (std::string name);

	/// <summary>
	/// 全てのモデルデータの破棄
	/// </summary>
	void AllRemove();


	/// <summary>
	/// Objファイルを読み込む
	/// </summary>
	ModelData LoadObjFile(const std::string& routeFilePath, const std::string& fileName);
	ModelData LoadObjFileAssimpVer(const std::string& routeFilePath, const std::string& fileName);
	ModelData LoadGLTF(const std::string& routeFilePath, const std::string& fileName, const std::string& textureName);
	void LoadModel(const std::string& path, const std::string fileName);
	

	/// <summary>
	/// Nodeの階層構造からSkeletonを作る
	/// </summary>
	Skeleton CreateSkeleton(const Node& rootNode);


#pragma region Get

#pragma endregion 


private: // メンバ関数

	/// <summary>
	/// 
	/// </summary>
	ModelDatas LoadOBJ(const std::string& path, const std::string& fileName);
	ModelDatas LoadGLTF(const std::string& path, const std::string& fileName);

	/// <summary>
	/// 一回読み込んだものは読み込まない
	/// </summary>
	bool CheckObjData(std::string filePath);

	/// <summary>
	/// mtlファイルを読み込む関数
	/// </summary>
	MaterialData LoadMaterialTemplateFile(const std::string& filePath, const std::string& fileName, const std::string& routeFilePath);

	/// <summary>
	/// Nodeの情報を読む
	/// </summary>
	Node ReadNode(aiNode* node);

	/// <summary>
	/// NodeからJointを作る
	/// </summary>
	int32_t CreateJoint(const Node& node, const optional<int32_t>& parent, vector<Joint>& joints);


	// MeshDataの解析
	MeshData ParseMeshData(const aiScene* scene);

	// MaterialDataの解析
	MaterialDataN ParseMaterialData(const aiScene* scene, const std::string& filePath, const std::string& format);


private: // メンバ変数

	// ObjDataResource
	map<std::string, unique_ptr<ObjDataResource>> objModelDatas_;

	uint32_t objHandle_ = 0;

	ModelData modelData_{};


	// モデルのマップ
	//unordered_map<string, unique_ptr<Model>> modelsMap_;
	std::unordered_map < std::string, ModelDatas> modelsMap_;
};

