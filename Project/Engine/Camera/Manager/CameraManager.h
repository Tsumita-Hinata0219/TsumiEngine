#pragma once

#include "GameObject/GameObject.h"
#include "../Resources/CameraResource.h"

/* CameraManagerクラス */
class CameraManager {

private: // シングルトンデザインパターン

	CameraManager() = default;
	~CameraManager() = default;
	CameraManager(const CameraManager&) = delete;
	const CameraManager& operator=(const CameraManager&) = delete;

public:

	// インスタンスの取得
	static CameraManager* GetInstance() {
		static CameraManager instance;
		return &instance;
	}

	// 初期化
	void Init();

	// データをセットする
	void ReSetData(const CameraData& data);

	// コマンドコール
	void CommandCall(UINT number);

#pragma region Accessor アクセッサ

	// カメラのリソースの取得
	const CameraData* GetResource() { return this->resource_; }

#pragma endregion 


private:

	// カメラのリソース
	const CameraData* resource_ = nullptr;
	// カメラ本体
	CameraData camera_{};
};

