#pragma once

#include <filesystem>

#include "../../Base/WinApp/WinApp.h"
#include "../../Base/DXCommon/DirectXCommon.h"
#include "../../CommandManager/CommandManager.h"
#include "../../View/RTVManager/RTVManager.h"
#include "JapaneseGlyphArray.h"

class ImGuiManager {

private:

	// コンストラクタ、デストラクタ
	ImGuiManager() = default;
	~ImGuiManager() = default;

public:

	// インスタンス取得
	static ImGuiManager* GetInstance();

	// 解放処理
	static  void Release();

	// 初期化
	static void Initialize();

	// フレーム開始
	static void BeginFrame();

	// フレーム終了
	static void EndFrame();
};