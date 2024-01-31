#pragma once

#define DIRECTINPUT_VERSION 0x0800 // DirectInputnoバージョン指定
#include <dinput.h>
#include <Xinput.h>
#define XINPUT_GAMEPAD_MAX 16

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib,"xinput.lib")
#pragma comment(lib, "dxguid.lib")

#include "WinApp.h"
#include "Struct.h"

#include <cassert>
#include <wrl.h>
#include <array>



struct PadData {
	Vector2 stickR_;
	Vector2 stickL_;
	WORD button_;
	float triggerR_;
	float triggerL_;
};



// -------------------------------------------------------------------------
// 入力
// -------------------------------------------------------------------------
// KeyInput : キーボード
// -------------------------------------------------------------------------
class KeysInput {

public: // メンバ関数

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	static KeysInput* GetInstance();

	/// <summary>
	/// 初期化処理
	/// </summary>
	static void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	static void BeginFrame();

	/// <summary>
	/// 押されていない
	/// </summary>
	static bool NoneKey(uint32_t keyNum);

	/// <summary>
	/// 押した瞬間
	/// </summary>
	static bool TriggerKey(uint32_t keyNum);

	/// <summary>
	/// 押しっぱなし
	/// </summary>
	static bool PressKeys(uint32_t keyNum);

	/// <summary>
	/// 離された瞬間
	/// </summary>
	static bool ReleaseKeys(uint32_t keyNum);


private: // メンバ変数

	ComPtr<IDirectInput8> directInput_ = nullptr;
	ComPtr<IDirectInputDevice8> keyboard_ = nullptr;

	BYTE Keys[256] = {};
	BYTE preKeys[256] = {};
};





// -------------------------------------------------------------------------
// 入力
// -------------------------------------------------------------------------
// GamePadInput : ゲームパッド
// -------------------------------------------------------------------------
class GamePadInput {

public: // メンバ関数

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	static GamePadInput* GetInstance();

	/// <summary>
	/// 初期化処理
	/// </summary>
	static void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	static void BeginFrame();

	/// <summary>
	/// パッドの更新
	/// </summary>
	static bool GetJoyState();

	/// <summary>
	/// 各ボタンのトリガー状態の初期化処理
	/// </summary>
	void ResetButtonTriggers();

	/// <summary>
	/// ジョイコンの入力の取得
	/// </summary>
	static bool GetJoyStickState();

	/// <summary>
	/// 押されていない
	/// </summary>
	static bool NoneButton(uint32_t button);

	/// <summary>
	/// 押した瞬間
	/// </summary>
	static bool TriggerButton(uint32_t button);

	/// <summary>
	/// 押しっぱなし
	/// </summary>
	static bool PressButton(uint32_t button);

	/// <summary>
	/// 離された瞬間
	/// </summary>
	static bool ReleaseButton(uint32_t button);

	/// <summary>
	/// Lスティック
	/// </summary>
	static Vector2 GetLStick(const float& mode = SHRT_MAX);

	/// <summary>
	/// Rスティック
	/// </summary>
	static Vector2 GetRStick(const float& mode = SHRT_MAX);



private: // メンバ変数

	XINPUT_STATE joyState_{};
	XINPUT_STATE preJoyState_{};

	WORD buttonTriggers[XINPUT_GAMEPAD_MAX];
};