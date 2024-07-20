#pragma once

#include "../../GameObject.h"
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

	// コマンドコール
	void CommandCall(UINT number);

private:

	// バッファー
	BufferResource<TransformationViewMatrix> buffer_;
};

