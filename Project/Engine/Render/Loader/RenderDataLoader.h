#pragma once

#include "Math/MyMath.h"

#include "../Structure/RenderStructure.h"
#include "TextureManager/TextureManager.h"

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <filesystem>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct aiScene;



namespace RenderSystem {

namespace FileFormat {
const std::pair<std::string, uint32_t> OBJ = { ".obj", 0 };
const std::pair<std::string, uint32_t> GLTF = { ".gltf", 1 };
}

namespace Loader {

/// <summary>
/// OBJファイルローダー
/// </summary>
Rendering::SceneData LoadObj(const std::string& path, const std::string& fileName)
{
	Rendering::SceneData result{};

	// return するModelDatasに名前を付けておく。(ファイル名)
	result.name = fileName.substr(0, fileName.size() - 4);
	result.fileFormat = GetExtension(fileName);

	// asssimpでobjを読む
	Assimp::Importer importer;
	string file = ("Resources/" + path + "/" + fileName);

	//三角形の並び順を逆にする。UVをフリップする(texcoord.y = 1.0f - texcoord.y;の処理)
	const aiScene* scene = 
		importer.ReadFile(file.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs);
	assert(scene->HasMeshes()); // メッシュがないのは対応しない

	// mesh & indicesを解析する
	result.mesh = ParseMeshData(scene, result.fileFormat);

	// materialを解析する
	result.material = ParseMaterialData(scene, path, result.fileFormat);

	// 各種フラグは折っておく
	result.light.enable = false;
	result.environment.enable = false;

	return result;
}


/// <summary>
/// GLTFファイルローダー
/// </summary>
Rendering::SceneData LoadGLTF(const std::string& path, const std::string& fileName)
{
	Rendering::SceneData result{};

	// return するModelDatasに名前を付けておく。(ファイル名)
	result.name = fileName.substr(0, fileName.size() - 5);
	result.fileFormat = GetExtension(fileName);

	// asssimpでobjを読む
	Assimp::Importer importer;
	string file = ("Resources/" + path + "/" + fileName);

	//三角形の並び順を逆にする。UVをフリップする(texcoord.y = 1.0f - texcoord.y;の処理)
	const aiScene* scene = 
		importer.ReadFile(file.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs);
	assert(scene->HasMeshes()); // メッシュがないのは対応しない

	// mesh & indicesを解析する
	result.mesh = ParseMeshData(scene, result.fileFormat);

	// materialを解析する
	result.material = ParseMaterialData(scene, path, result.fileFormat);

	// 各種フラグは折っておく
	result.light.enable = false;
	result.environment.enable = false;

	return result;
}


/// <summary>
/// MeshDataの解析
/// </summary>
Mesh::MeshData ParseMeshData(const aiScene* scene, std::string fileFormat)
{
	Mesh::MeshData result{};

	// mesh & indicesを解析する
	// 今回作るmesh & indeces
	for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex) {
		aiMesh* mesh = scene->mMeshes[meshIndex];
		assert(mesh->HasNormals());
		assert(mesh->HasTextureCoords(0));
		result.vertices.resize(mesh->mNumVertices); // 最初に頂点数分のメモリを確保しておく

		// Verticesを解析する
		for (uint32_t vertexIndex = 0; vertexIndex < mesh->mNumVertices; ++vertexIndex) {
			aiVector3D& position = mesh->mVertices[vertexIndex];
			aiVector3D& normal = mesh->mNormals[vertexIndex];
			aiVector3D& texcoord = mesh->mTextureCoords[0][vertexIndex];

			// 右手系 -> 左手系への変換
			result.vertices[vertexIndex].position = { -position.x, position.y, position.z, 1.0f };
			result.vertices[vertexIndex].normal = { -normal.x, normal.y, normal.z };
			result.vertices[vertexIndex].texCoord = { texcoord.x, texcoord.y };
		}

		// Indexを解析する
		for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex) {
			aiFace& face = mesh->mFaces[faceIndex];
			assert(face.mNumIndices == 3);

			for (uint32_t element = 0; element < face.mNumIndices; ++element) {
				uint32_t vertexIndex = face.mIndices[element];
				result.indices.push_back(vertexIndex);
			}
		}

		// フォーマットがGLTFならBoneの解析に入る
		if (fileFormat == FileFormat::GLTF.first) {

			for (uint32_t boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex) {

				// Jointごとの格納領域を作る
				aiBone* bone = mesh->mBones[boneIndex];
				string jointName = bone->mName.C_Str();
				Skinning::JointWeight& jointWeightData = result.skinClusterData[jointName];

				// InverseBindPoseMatrixの抽出
				aiMatrix4x4 bindPoseMatrixAssimp = bone->mOffsetMatrix.Inverse(); // BindPoseMatrixに戻す
				aiVector3D scale, translate;
				aiQuaternion rotate;
				bindPoseMatrixAssimp.Decompose(scale, rotate, translate); // 成分を抽出
				// 左手系のBindPoseMatrixを作る
				Matrix4x4 bindPoseMatrix = MakeAffineMatrix(
					{ scale.x, scale.y, scale.z },
					{ rotate.w, rotate.x, -rotate.y, -rotate.z },
					{ -translate.x, translate.y, translate.z });
				// InverseBindPoseMatrixにする
				jointWeightData.inverseBindPoseMatrix = Inverse(bindPoseMatrix);
				Matrix4x4 hr = jointWeightData.inverseBindPoseMatrix * bindPoseMatrix;

				// Weight情報を取り出す
				for (uint32_t weightIndex = 0; weightIndex < bone->mNumWeights; ++weightIndex) {
					jointWeightData.vertexWeights.push_back({ bone->mWeights[weightIndex].mWeight, bone->mWeights[weightIndex].mVertexId });
				}
			}
		}
	}

	// Nodeの読み込み
	result.rootNode = ReadNode(scene->mRootNode);

	return result;
}

/// <summary>
/// MaterialDataの解析
/// </summary>
Material::MaterialData ParseMaterialData(const aiScene* scene, const std::string& filePath, const std::string& format)
{
	Material::MaterialData result{};

	for (uint32_t materialIndex = 0; materialIndex < scene->mNumMaterials; ++materialIndex) {
		aiMaterial* material = scene->mMaterials[materialIndex];

		if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
			aiString textureFilePath;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilePath);

			// FileFormatで読み込みパスの分岐
			if (format == FileFormat::OBJ.first) {
				result.textureHandle = TextureManager::LoadTexture(filePath, textureFilePath.C_Str());
			}
			else if (format == FileFormat::GLTF.first) {
				result.textureHandle = TextureManager::LoadTexture(filePath, textureFilePath.C_Str());
			}
		}

		// マテリアルの名前の設定
		// 複数マテリアルは今は非対応。ファイルの名前をそのままマテリアルの名前へ
		result.name = material->GetName().C_Str();
	}

	return result;
}

/// <summary>
/// Nodeの情報を読み込む
/// </summary>
Skinning::Node ReadNode(aiNode* node)
{
	Skinning::Node result;

	aiMatrix4x4 aiLocalMatrix = node->mTransformation; // nodeのlocalMatrixを取得
	aiLocalMatrix.Transpose(); // 列ベクトル形式を行ベクトル形式に転置


	aiVector3D scale, translate;
	aiQuaternion rotate;

	// assimpの行列からSRTを抽出する関数を利用
	node->mTransformation.Decompose(scale, rotate, translate);

	// scaleはそのまま
	result.transform.scale = { scale.x, scale.y,scale.z };

	// x軸を反転、さらに回転方向が逆なので軸を反転させる
	result.transform.rotate = { rotate.w, rotate.x, -rotate.y, -rotate.z };

	// x軸を反転
	result.transform.translate = { -translate.x, translate.y,translate.z };

	// 上記で読み込んだ情報を元にLocalMatrixを求める
	result.localMatrix = MakeAffineMatrix(result.transform.scale, result.transform.rotate, result.transform.translate);

	result.name = node->mName.C_Str(); // Mode名を格納
	result.Children.resize(node->mNumChildren); // 子供の数だけ確保
	for (uint32_t childIndex = 0; childIndex < node->mNumChildren; ++childIndex) {
		// 再帰的によんで階層構造を作っていく
		result.Children[childIndex] = ReadNode(node->mChildren[childIndex]);
	}
	return result;
}

}
}