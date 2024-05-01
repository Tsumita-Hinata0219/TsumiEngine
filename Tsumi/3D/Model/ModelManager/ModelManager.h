#pragma once

#include "MyMath.h"
#include "Struct.h"
#include "TextureManager.h"
#include "ObjDataResource.h"
#include <map>
#include <fstream>
#include <sstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


/* ModelManagerクラス */
class ModelManager {

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ModelManager() {};
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ModelManager() {};

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	static ModelManager* Getinstance();

	/// <summary>
	/// 解放処理
	/// </summary>
	static void Finalize();

	/// <summary>
	/// Objファイルを読み込む
	/// </summary>
	ModelData LoadObjFile(const std::string& routeFilePath, const std::string& fileName);
	ModelData LoadObjFileAssimpVer(const std::string& routeFilePath, const std::string& fileName);
	ModelData LoadGLTF(const std::string& routeFilePath, const std::string& fileName, const std::string& textureName);

	/// <summary>
	/// Nodeの階層構造からSkeletonを作る
	/// </summary>
	Skeleton CreateSkeleton(const Node& rootNode);


private: // メンバ関数

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


private: // メンバ変数

	// ObjDataResource
	map<std::string, unique_ptr<ObjDataResource>> objModelDatas_;

	uint32_t objHandle_ = 0;

	ModelData modelData_{};
};

