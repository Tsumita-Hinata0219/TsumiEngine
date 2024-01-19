#pragma once
#include <Windows.h>
#include <cstdint>
#include <string>
#include <format>
#include "imgui.h"
#include "imgui_impl_dx12.h"
#include "imgui_impl_win32.h"



// ImGuiのなんか。忘れた。なにこれ
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


class WinApp
{
public: ///// メンバ関数 /////

	/// <summary>
	/// WinAppのインスタンスの取得
	/// </summary>
	static WinApp* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	static void Initialize(const wchar_t* title);

	/// <summary>
	/// メッセージの処理
	/// </summary>
	/// <returns>終了かどうか</returns>
	static bool ProcessMessage();


#pragma region Get 取得

	/// <summary>
	/// クライアントサイズの取得
	/// </summary>
	static int32_t GetClientWidth() { return WinApp::GetInstance()->ClientWidth_; }
	static int32_t GetCliendHeight() { return WinApp::GetInstance()->ClientHeight_; }

	/// <summary>
	/// ウィンドウハンドルの取得
	/// </summary>
	static HWND GetHwnd() { return WinApp::GetInstance()->hwnd_; };

	/// <summary>
	/// ウィンドウクラスの取得
	/// </summary>
	static WNDCLASS GetWc() { return WinApp::GetInstance()->wc_; }

	/// <summary>
	/// メッセージの取得
	/// </summary>
	static MSG GetMsg() { return WinApp::GetInstance()->msg_; }

#pragma endregion


private: ///// メンバ関数 /////

	/// <summary>
	/// ウィンドウプロシージャ
	/// </summary>
	static LRESULT CALLBACK WindowProc(
		HWND hwnd,
		UINT msg,
		WPARAM wparam,
		LPARAM lparam);

	/// <summary>
	/// ゲームウィンドウの作成
	/// </summary>
	static void CreateGameWindow();



private: ///// メンバ変数 /////

	// タイトルバー
	const wchar_t* title_;
	// クライアントサイズ
	static const int32_t ClientWidth_ = 1280;
	static const int32_t ClientHeight_ = 720;

	// メッセージ
	MSG msg_{};
	// ウィンドウクラス
	WNDCLASS wc_{};
	// ウィンドウハンドル
	HWND hwnd_ = nullptr;
};
