#include "Input.h"



//
//// -------------------------------------------------------------------------
//// KeyInput : キーボード
//// -------------------------------------------------------------------------
//
//// インスタンスの取得
//KeyInput* KeyInput::GetInstance() {
//	static KeyInput instance;
//	return &instance;
//}
//
//// 初期化処理
//void KeyInput::Initialize() {
//
//	// DirectInputのインスタンス生成
//	HRESULT result = DirectInput8Create(
//		WinApp::GetWc().hInstance, DIRECTINPUT_VERSION, 
//		IID_IDirectInput8, (void**)&KeyInput::GetInstance()->directInput_, nullptr);
//	assert(SUCCEEDED(result));
//
//	// キーボードデバイス生成
//	result = KeyInput::GetInstance()->directInput_->CreateDevice(GUID_SysKeyboard, &KeyInput::GetInstance()->keyboard_, NULL);
//	assert(SUCCEEDED(result));
//
//	// 入力データ形式のセット
//	result = KeyInput::GetInstance()->keyboard_->SetDataFormat(&c_dfDIKeyboard);
//	assert(SUCCEEDED(result));
//
//	// 排他制御レベルのセット
//	result = KeyInput::GetInstance()->keyboard_->SetCooperativeLevel(
//		WinApp::GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
//	assert(SUCCEEDED(result));
//}
//
//// 更新処理
//void KeyInput::BeginFrame() {
//
//	// メモリコピー
//	memcpy(KeyInput::GetInstance()->preKeys, KeyInput::GetInstance()->Keys, 256);
//
//	// キーボード情報の取得開始
//	KeyInput::GetInstance()->keyboard_->Acquire();
//
//	// 全キーの入力状態を取得する
//	KeyInput::GetInstance()->keyboard_->GetDeviceState(sizeof(KeyInput::GetInstance()->Keys), KeyInput::GetInstance()->Keys);
//}
//
//// 押されていない
//bool KeyInput::NoneKey(uint32_t keyNum) {
//
//	if (KeyInput::GetInstance()->preKeys[keyNum] == 0x00 && KeyInput::GetInstance()->Keys[keyNum] == 0x00) {
//		return true;
//	}
//	return false;
//}
//
//// 押した瞬間
//bool KeyInput::TriggerKey(uint32_t keyNum) {
//
//	if (KeyInput::GetInstance()->preKeys[keyNum] == 0x00 && KeyInput::GetInstance()->Keys[keyNum] == 0x80) {
//		return true;
//	}
//	return false;
//}
//
//// 押しっぱなし
//bool KeyInput::PressKeys(uint32_t keyNum) {
//
//	if (KeyInput::GetInstance()->preKeys[keyNum] == 0x80 && KeyInput::GetInstance()->Keys[keyNum] == 0x80) {
//		return true;
//	}
//	return false;
//}
//
//// 離された瞬間
//bool KeyInput::ReleaseKeys(uint32_t keyNum) {
//
//	if (KeyInput::GetInstance()->preKeys[keyNum] == 0x80 && KeyInput::GetInstance()->Keys[keyNum] == 0x00) {
//		return true;
//	}
//	return false;
//}
//
//// -------------------------------------------------------------------------
//// KeyInput : キーボード
//// -------------------------------------------------------------------------
//
//
//
//
//
//// -------------------------------------------------------------------------
//// GamePadInput : ゲームパッド
//// -------------------------------------------------------------------------
//
//// インスタンスの取得
//GamePadInput* GamePadInput::GetInstance() {
//	static GamePadInput instance;
//	return &instance;
//}
//
//// 初期化処理
//void GamePadInput::Initialize() {
//
//}
//
//// 更新処理
//void GamePadInput::BeginFrame() {
//
//}
//
//
//// -------------------------------------------------------------------------
//// GamePadInput : ゲームパッド
//// -------------------------------------------------------------------------
//
