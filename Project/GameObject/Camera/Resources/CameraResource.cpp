#include "CameraResource.h"



// 初期化処理
void CameraResource::Init(Vector3 initRotate, Vector3 initTranslate)
{
	// 初期姿勢と座標
	srt.rotate = initRotate;
	srt.translate = initTranslate;

	// 行列の計算を通しておく
	UpdateMatrix();
}


// 行列の更新
void CameraResource::UpdateMatrix()
{
	// 回転行列を作成
	rotateMat = MakeRotateXYZMatrix(srt.rotate);

	// 平行移動行列を作成
	translateMat = MakeTranslateMatrix(srt.translate);

	// ワールド行列を作成
	matWorld = MakeAffineMatrix(srt.scale, srt.rotate, srt.translate);

	// ビュー行列を作成（カメラの位置と向きを基に逆行列を計算）
	viewMatrix = Inverse(matWorld);

	// 投影行列を作成（透視投影）
	projectionMatrix = MakePerspectiveFovMatrix(fov, aspectRatio, nearZ, farZ);

	// 投影逆行列
	projectionInverseMatrix = Inverse(projectionMatrix);

	// 正射影行列を作成（ウィンドウサイズを基に設定）
	orthoGraphicMatrix = MakeOrthographicMatrix(0.0f, 0.0f, float(WinApp::kWindowWidth), float(WinApp::kWindowHeight), 0.0f, 100.0f);

	// ビューポート行列を作成（ウィンドウサイズを基に設定）
	viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, float(WinApp::kWindowWidth), float(WinApp::kWindowHeight), 0.0f, 1.0f);

	// ビュープロジェクション行列
	viewProjectionMatrix = projectionMatrix * viewMatrix;

	// ビュー・投影・ビューポート行列を掛け合わせた行列を作成
	viewProjectionViewportMatrix = viewportMatrix * viewProjectionMatrix;

	// ビュー・投影・ビューポート行列の逆行列を作成
	inverseViewProjectionViewportMatrix = Inverse(viewProjectionViewportMatrix);


	// 行列に書き込むデータの設定
	TransfarMatrix();
}


// 行列に書き込むデータの設定
void CameraResource::TransfarMatrix()
{
	bufferData->view = viewMatrix;
	bufferData->viewProjection = projectionMatrix;
	bufferData->orthoGraphic = orthoGraphicMatrix;
	bufferData->cameraPosition = GetWorldPosition();
}


// ワールド座標の取得
Vector3 CameraResource::GetWorldPosition()
{
	return { matWorld.m[3][0], matWorld.m[3][1], matWorld.m[3][2] };
}
