#pragma once

#define DIRECTINPUT_VERSION 0x0800 // DirectInputnoバージョン指定
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include "WinApp.h"
#include "Struct.h"

#include <cassert>
#include <wrl.h>
#include <array>



// -------------------------------------------------------------------------
// 入力
// -------------------------------------------------------------------------
// 
// -------------------------------------------------------------------------
class Input {

public: // メンバ関数

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	static Input* GetInstance() {
		static Input instance;
		return &instance;
	}

	/// <summary>
	/// 初期化処理
	/// </summary>
	static void Initialize() {
		/*keyInput_ = make_unique<KeyInput>();
		KeyInput::GetInstance()->Initialize();*/
	}

	/// <summary>
	/// 更新処理
	/// </summary>
	static void BeginFrame() {
		/*KeyInput::GetInstance()->BeginFrame()*/;
	}
//
//private:
//
//	unique_ptr<KeyInput> keyInput_ = nullptr;

};

//
//
//
//// -------------------------------------------------------------------------
//// 入力
//// -------------------------------------------------------------------------
//// KeyInput : キーボード
//// -------------------------------------------------------------------------
//class KeyInput {
//
//public: // メンバ関数
//
//	/// <summary>
//	/// インスタンスの取得
//	/// </summary>
//	static KeyInput* GetInstance();
//
//	/// <summary>
//	/// 初期化処理
//	/// </summary>
//	static void Initialize();
//
//	/// <summary>
//	/// 更新処理
//	/// </summary>
//	static void BeginFrame();
//
//	/// <summary>
//	/// 押されていない
//	/// </summary>
//	static bool NoneKey(uint32_t keyNum);
//
//	/// <summary>
//	/// 押した瞬間
//	/// </summary>
//	static bool TriggerKey(uint32_t keyNum);
//
//	/// <summary>
//	/// 押しっぱなし
//	/// </summary>
//	static bool PressKeys(uint32_t keyNum);
//
//	/// <summary>
//	/// 離された瞬間
//	/// </summary>
//	static bool ReleaseKeys(uint32_t keyNum);
//
//
//private: // メンバ変数
//
//	ComPtr<IDirectInput8> directInput_ = nullptr;
//	ComPtr<IDirectInputDevice8> keyboard_ = nullptr;
//
//	BYTE Keys[256] = {};
//	BYTE preKeys[256] = {};
//};
//
//
//
//
//
//// -------------------------------------------------------------------------
//// 入力
//// -------------------------------------------------------------------------
//// GamePadInput : ゲームパッド
//// -------------------------------------------------------------------------
//class GamePadInput {
//
//public: // メンバ関数
//
//	/// <summary>
//	/// インスタンスの取得
//	/// </summary>
//	static GamePadInput* GetInstance();
//
//	/// <summary>
//	/// 初期化処理
//	/// </summary>
//	static void Initialize();
//
//	/// <summary>
//	/// 更新処理
//	/// </summary>
//	static void BeginFrame();
//
//
//
//private: // メンバ変数
//
//
//};