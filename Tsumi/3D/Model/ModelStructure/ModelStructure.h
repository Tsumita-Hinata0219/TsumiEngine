#pragma once


#include "../../../Project/Math/MyMath.h"
#include "../../../Project/Math/Struct.h"


// メッシュデータ
struct MeshData {
	std::vector<VertexData> vertices;
	std::vector<uint32_t> indices;
	Node rootNode;
};

// マテリアルデータ
struct MaterialDataN {
	Vector4 color = Vector4::one;
	Matrix4x4 uvTransform = Matrix4x4::identity;
	uint32_t textureHandle = 1u;
	std::string name = "default";
};

// ライトデータ
struct DirectionalLightData
{
	Vector4 color = Vector4::one; // 色(RGBA)
	Vector3 direction = { 0.0f, 1.0f, 0.0f }; // ライトの向き
	float intensity = 1.0f; // 輝度
	float shininess = 1.0f; // 光沢
	bool eneble = true; // フラグ

	void DrawImGui(std::string label = "") {
		ImGui::Checkbox((label + "_enable").c_str(), &eneble);
		ImGui::ColorEdit4((label + "_color").c_str(), &color.x);
		ImGui::DragFloat3((label + "_direction").c_str(), &direction.x, 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat((label +  "_intennsity").c_str(), &intensity, 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat((label + "_shininess").c_str(), &shininess, 0.01f, 0.0f, 1.0f);
	}
};

// 環境マップデータ
struct EnvironmentData {
	int texture = 0;
	float scale = 0.0f;
	bool enable = false;

	void DrawImGui(std::string label = "") {
		ImGui::Checkbox((label + "_Enable").c_str(), &enable);
		ImGui::DragFloat((label + "_Scale").c_str(), &scale);
	}
};