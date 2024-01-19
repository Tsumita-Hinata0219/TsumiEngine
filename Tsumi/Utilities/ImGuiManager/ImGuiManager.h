#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"

class ImGuiManager {
public:
	static ImGuiManager* GetInstance();
	static void Initialize();
	static void BeginFrame();
	static void EndFrame();
};