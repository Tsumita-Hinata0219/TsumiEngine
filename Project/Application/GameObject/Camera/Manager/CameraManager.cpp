#include "CameraManager.h"



// 初期化処理
void CameraManager::Init()
{
	// データの初期化
	resource_ = nullptr;
}


// バッファーに書き込む
void CameraManager::ReSetData(const CameraResource& data)
{
	resource_ = nullptr;
	resource_ = &data;
}


// コマンドコール
void CameraManager::CommandCall(UINT number)
{
	resource_->buffer->CommandCall(number);
}