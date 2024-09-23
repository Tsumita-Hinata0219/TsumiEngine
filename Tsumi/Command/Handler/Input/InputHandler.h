#pragma once

#include "../../ICommand.h"
#include "../../../Input/Input.h"
#include <unordered_map>
#include <iostream>


/* 入力に基づいてコマンドを呼び出すクラス */
class InputHandler {

private: // シングルトン

	InputHandler() = default;
	~InputHandler() = default;
	InputHandler(const InputHandler&) = delete;
	const InputHandler& operator=(const InputHandler&) = delete;


public:

	// インスタンス取得
	static InputHandler* GetInstance() {
		static InputHandler instance;
		return &instance;
	}

	// 初期化
	void Init();

	// 入力に応じてコマンドを実行
	void HandlerExecute(uint32_t input);

	// 終了処理
	void HandleRelease(uint32_t input);

	// コマンドの登録
	static void RegisterCommand(uint32_t input, std::unique_ptr<ICommand> command);

	// コマンドの解放
	void Clear();


private:

	// コマンド配列
	std::unordered_map<uint32_t, std::unique_ptr<ICommand>> commandMap_;

};

