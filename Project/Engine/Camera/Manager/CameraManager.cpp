#include "CameraManager.h"



// 初期化処理
void CameraManager::Init()
{
	// データの初期化
	resource_ = nullptr;
	// カメラリソース
	camera_.Init();
	camera_.Update();
	ReSetData(camera_);

	// データ作成
	cameraData_ = std::make_shared<CameraData>();
	cameraData_->Init();
	// バッファー作成
	cameraBuffer_.CreateCBV();
}


// バッファーに書き込む
void CameraManager::ReSetData(const CameraData& data)
{
	resource_ = nullptr;
	resource_ = &data;
}


// コマンドコール
void CameraManager::CommandCall(UINT number)
{
	resource_->buffer->BindGraphicsCBV(number);
}


// カメラデータのバインド
void CameraManager::Bind_CameraData(UINT num)
{
	cameraBuffer_.UpdateData(cameraData_.get());
	cameraBuffer_.BindComputeCBV(num);
}
