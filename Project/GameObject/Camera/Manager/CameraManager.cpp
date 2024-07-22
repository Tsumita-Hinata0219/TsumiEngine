#include "CameraManager.h"



// 初期化処理
void CameraManager::Init()
{
	// データの初期化
	resource_ = nullptr;

	// バッファー作成
	buffer_.CreateResource();
}


// バッファーに書き込む
void CameraManager::ReSetData(const CameraResource& data)
{
	resource_ = nullptr;
	resource_ = &data;
}


// バッファーに書き込む
void CameraManager::WrirwData()
{
	// データ書き込み
	buffer_.Map();
	buffer_.WriteData(resource_->bufferData);
	buffer_.UnMap();
}


// コマンドコール
void CameraManager::CommandCall(UINT number)
{
	buffer_.CommandCall(number);
}
