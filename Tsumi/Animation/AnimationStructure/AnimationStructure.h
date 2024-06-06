#pragma once

#include "MyMath.h"
#include <span>
#include <vector>
#include <memory>
#include <array>
#include <string>
#include <optional>
#include <map>



// QuaternionTransform
struct QuaternionTransform {
	Vector3 scale;
	Quaternion rotate;
	Vector3 translate;
};


// Joint
struct Joint {
	QuaternionTransform transform; // Transform構造体
	Matrix4x4 localMatrix; // localMatrix
	Matrix4x4 skeletonSpaceMatrix; // skeltonSpaceでの変換行列
	string name; // 名前
	vector<int32_t> children; // 子NodeのIndexのリスト。いなければ空
	int32_t index; // 自身のIndex
	optional<int32_t> parent; // 親JointのInsex。いなければnull
};


// VertexWeightData
struct VertexWeightData {
	float weight;
	uint32_t vertexIndex;
};


// JointWeightData
struct JointWeightData {
	Matrix4x4 inverseBindPoseMatrix;
	std::vector<VertexWeightData> vertexWeights;
};


// Node
struct Node {
	QuaternionTransform transform;
	Matrix4x4 localMatrix;
	std::string name;
	std::vector<Node> Children;
};


// VertexInfluence
const uint32_t kNumMaxInfluence = 4;
struct VertexInfluence {
	std::array<float, kNumMaxInfluence> weights;
	std::array<int32_t, kNumMaxInfluence> jointIndices;
};


// WellForGPU
struct WellForGPU {
	Matrix4x4 skeletonSpaceMatrix; // 位置用
	Matrix4x4 skeletonSpaceInverseTransposeMatrix; // 法線用
};


// SkinCluster
struct SkinCluster {
	std::vector<Matrix4x4> inverseBindPosematrices;
	Microsoft::WRL::ComPtr<ID3D12Resource> influenceResource;
	D3D12_VERTEX_BUFFER_VIEW influenceBufferView;
	std::span<VertexInfluence> mappedInfluence;
	Microsoft::WRL::ComPtr<ID3D12Resource> paletteResource;
	std::span<WellForGPU> mappedPallette;
	std::pair<D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_GPU_DESCRIPTOR_HANDLE>paletteSrvHandle;
};


// Skeleton
struct Skeleton {
	int32_t root; // RootJointのIndex
	std::map<std::string, int32_t> jointMap; // Joint名とIndexとの辞書
	vector<Joint> joints; // 所属しているジョイント
};

