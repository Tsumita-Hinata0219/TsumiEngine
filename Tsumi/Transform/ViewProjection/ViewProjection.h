#pragma once

#include "WinApp.h"
#include "MyMath.h"
#include "CreateResource.h"
#include <Struct.h>



/* ビュープロジェクション変換データ */
struct ViewProjection {

#pragma region ビュー行列の設定

	// X, Y, Z軸周りのローカル回転軸
	Vector3 rotate = { 0.0f, 0.0f, 0.0f };

	// ローカル座標
	Vector3 translate = { 0.0f, 0.0f, -15.0f };

#pragma endregion 


#pragma region 射影行列の設定

	// 垂直方向視野角
	float fov = 0.45f;

	// ビューポートのアスペクト比
	float aspectRatio = float(WinApp::GetClientWidth()) / float(WinApp::GetCliendHeight());

	// 深度限界 (手前側)
	float nearZ = 0.1f;

	// 深度限界 (奥側)
	float farZ = 1000.0f;

#pragma endregion 


	// ビュー行列
	Matrix4x4 matView{};

	// 射影行列
	Matrix4x4 matProjection{};

	// 正射影行列
	Matrix4x4 orthoGraphicMat{};


	// 定数バッファ
	ComPtr<ID3D12Resource> constBuffer;

	// マッピング済みアドレス
	TransformationViewMatrix* constMap = nullptr;



	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(Vector3 initRotate = { 0.0f, 0.0f, 0.0f }, Vector3 initTranslate = { 0.0f, 0.0f, -5.0f });

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