#pragma once

#include "../../Project/Math/MyMath.h"
#include "../../Project/Math/Struct.h"
#include "../CreateResource/CreateResource.h"

#include <vector>



// 定数バッファ構造体
struct TransformationMat {
	Matrix4x4 World;
	Matrix4x4 WVP;
	Matrix4x4 WorldInverseTranspose;
};


/* Transform構造体 */
struct Transform
{
	// ローカルスケール
	Vector3 scale = Vector3::one;
	// ローカル回転軸
	Vector3 rotate = Vector3::zero;
	// ローカル座標
	Vector3 translate = Vector3::zero;

	// ローカル -> ワールド変換行列
	Matrix4x4 matWorld{};

	// TransformationMatに設定する変数
	TransformationMat transformationMatData{};

	// ペアレント
	const Transform* parent{};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 行列の更新処理
	/// </summary>
	void UpdateMatrix();


#pragma region Get

	/// <summary>
	/// ワールド座標の取得
	/// </summary>
	Vector3 GetWorldPos();

#pragma endregion

#pragma region Set

	/// <summary>
	/// 親子関係を結ぶ
	/// </summary>
	void SetParent(const Transform* parentTransform);

#pragma endregion
};
