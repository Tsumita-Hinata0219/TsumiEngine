#pragma once

#include "../../ICommand.h"
#include "../../../Input/Input.h"
#include <unordered_map>
#include <iostream>


/* 入力に基づいてコマンドを呼び出すクラス */
class InputHandler {

public:

	// コンストラクタ、デストラクタ
	InputHandler() = default;
	~InputHandler();

	// 初期化
	void Init();

	// 入力に応じてコマンドを実行
	void HandlerExecute(uint32_t input);

	// 終了処理
	void HandleRelease(uint32_t input);

	// コマンドの登録
	void RegisterCommand(uint32_t input, ICommand* command);


private:

	// コマンド配列
	std::unordered_map<uint32_t, ICommand*> commandMap_;

};

