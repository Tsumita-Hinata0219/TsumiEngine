#pragma once

#include "MyMath.h"
#include"QuaternionTransform.h"


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