#include "ViewProjection.h"



// 初期化処理
void ViewProjection::Initialize(Vector3 initRotate, Vector3 initTranslate) {

	rotate = initRotate;
	translate = initTranslate;

	CreateBuffer();
	Map();
	UpdateMatrix();
}


// 更新処理
void ViewProjection::UpdateMatrix() {

	Matrix4x4 translateMat = MakeTranslateMatrix(translate);
	Matrix4x4 rotateMat = MakeRotateXYZMatrix(rotate.x, rotate.y, rotate.z);

	matView = Inverse(translateMat) * Inverse(rotateMat);
	matProjection = MakePerspectiveFovMatrix(fov, aspectRatio, nearZ, farZ);
	orthoGraphicMat = MakeOrthographicMatrix(0.0f, 0.0f, float(WinApp::GetClientWidth()), float(WinApp::GetCliendHeight()), 0.0f, 100.0f);

	TransferMatrix();
}


// 定数バッファの生成
void ViewProjection::CreateBuffer() {

	CreateResource::CreateBufferResource(sizeof(TransformationViewMatrix), constBuffer);

	// constBuffer が nullptr の場合はエラーログを出力してアサーションでプログラムを停止させる
	if (!constBuffer) {
		assert(false && "Failed to create constBuffer.");
	}
}


// マッピングする
void ViewProjection::Map() {

	// constBuffer が nullptr の場合はエラーハンドリング
	if (!constBuffer) {
		// エラーログなどを出力するか、適切な対処を行う
		// この例ではエラーログを出力し、アサーションでプログラムを停止させる
		assert(false && "constBuff_ is nullptr. Make sure to create constBuffer before calling Map.");
		return;
	}

	HRESULT result = constBuffer->Map(0, nullptr, reinterpret_cast<void**>(&constMap));
	assert(SUCCEEDED(result));
}


// マッピング終了
void ViewProjection::UnMap() {

	constBuffer->Unmap(0, nullptr);
}


// 行列の計算・転送
void ViewProjection::TransferMatrix() {

	Map();

	constMap->view = matView;
	constMap->viewProjection = matProjection;
	constMap->orthoGraphic = orthoGraphicMat;

	constMap->position = translate;

	UnMap();
}