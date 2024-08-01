#include "IGLTFState.h"
#include "../../Project/GameObject/Camera/Manager/CameraManager.h"


// コンストラクタ
IGLTFState::IGLTFState(ModelDatas datas)
{
	// CameraManagerのインスタンスの取得
	cameraManager_ = CameraManager::GetInstance();

	// ModelDatasの設定
	datas_ = datas;

	// DatasをもとにBufferを作成
	CreateBufferResource();
}

// 描画処理
void IGLTFState::Draw(Transform transform)
{
	transform;
}


// コマンドコール
void IGLTFState::CommandCall()
{
}
