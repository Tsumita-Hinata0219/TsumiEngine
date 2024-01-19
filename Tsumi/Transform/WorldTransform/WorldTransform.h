#pragma once
#include "MyMath.h"
#include "CreateResource.h"

#include <vector>


struct TransformationMatrix {
	Matrix4x4 WVP;
	Matrix4x4 World;
};

/// <summary>
/// ワールド変換データ
/// </summary>
struct WorldTransform {

	// ローカルスケール
	Vector3 scale = { 1.0f, 1.0f, 1.0f };
	// ローカル回転軸
	Vector3 rotate = { 0.0f, 0.0f, 0.0f };
	// ローカル座標
	Vector3 translate = { 0.0f, 0.0f, 0.0f };

	// ローカル -> ワールド変換行列
	Matrix4x4 matWorld{};

	// ペアレント
	const WorldTransform* parent{};

	// 定数バッファー
	ComPtr<ID3D12Resource> constBuffer = nullptr;

	//// マッピング済みアドレス
	TransformationMatrix* constMap;
	//TransformationMatrix* buffMap;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 行列の更新処理
	/// </summary>
	void UpdateMatrix();

	/// <summary>
	/// 定数バッファの生成
	/// </summary>
	void CreateBuffer();

	/// <summary>
	/// マッピングする
	/// </summary>
	void Map();

	/// <summary>
	/// マッピング終了
	/// </summary>
	void UnMap();

	/// <summary>
	/// 行列の計算・転送
	/// </summary>
	void TransferMatrix();
};
