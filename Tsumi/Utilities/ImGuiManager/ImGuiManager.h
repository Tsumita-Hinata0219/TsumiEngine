#pragma once
#include "../WinApp/WinApp.h"
#include "DirectXCommon.h"
#include "CommandManager.h"
#include "RTVManager.h"
#include "JapaneseGlyphArray.h"

class ImGuiManager {
public:
	static ImGuiManager* GetInstance();
	static void Initialize();
	static void BeginFrame();
	static void EndFrame();
};