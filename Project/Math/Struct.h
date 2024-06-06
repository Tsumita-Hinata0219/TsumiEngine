#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <dxcapi.h>

#include <wrl.h>
using Microsoft::WRL::ComPtr;
using namespace std;

#include <vector>
#include <iostream>
#include <cstdint>
#include <WorldTransform.h>
#include <optional>
#include <map>

#include "MyMath.h"

#include "AnimationStructure.h"
struct Node;
struct JointWeightData;



// 頂点データ
struct VertexData {
	Vector4 position;
	Vector2 texCoord;
	Vector3 normal;
};


// スプライト構造体
struct SpriteData {
	Vector4 topLeft;
	Vector4 bottomLeft;
	Vector4 topRight;
	Vector4 bottomRight;
};


// uvTransform
struct UVTransform {
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};

// 球
struct SphereData {
	Vector3 center;
	float radius;
};

// EulerTransform
struct EulerTransform {
	Vector3 scale;
	Vector3 rotate; // Eulerでの回転
	Vector3 translate;
};


// マテリアル
struct Material {
	Vector4 color;
};
struct MaterialSprite {
	Vector4 color;
	Matrix4x4 uvTransform;
};
struct MaterialParticle {
	Vector4 color;
	Matrix4x4 uvTransform;
};


// マテリアルデータ
struct MaterialData {
	std::string textureFilePath;
};


// モデルデータ
struct ModelData {
	std::map<string, JointWeightData> skinClusterData;
	std::vector<VertexData> vertices;
	std::vector<uint32_t> indices;
	MaterialData material;
	uint32_t textureHD;
	Node rootNode;
};


// 平行光源
struct DirectionalLight {
	Vector4 color{};          // ライトの色
	Vector3 direction{};      // ライトの向き
	//Vector3 SpecularFColor; // 鏡面反射色
	float intensity{};        // 輝度
	float sininess{};         // 光沢度
	bool enableLightting{};   // ライティングするか
};


// CompileShader
struct CompileShaders {
	IDxcBlobEncoding* Source;
	DxcBuffer SourceBuffer{};
	IDxcResult* Result;
	IDxcBlobUtf8* Error;
	IDxcBlob* Blob;
};


// Objデータ
struct ObjData {
	uint32_t index;
	vector<VertexData> vertices;
	MaterialData material;
	Node node;
};


struct ParticleTransformationMatrix {
	Matrix4x4 World;
	Vector4 Color;
	Matrix4x4 uvTansform;
};