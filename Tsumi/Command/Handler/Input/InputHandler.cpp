#include "InputHandler.h"



// デストラクタ
InputHandler::~InputHandler()
{
	// コマンドのクリーンアップ
	for (auto& pair : commandMap_)
	{
		delete pair.second;
	}
}


// 初期化
void InputHandler::Init()
{


}


// 入力に応じてコマンドを実行
void InputHandler::HandlerExecute(uint32_t input)
{
	if (commandMap_.find(input) != commandMap_.end()) 
	{
		commandMap_[input]->Execute();
	}
}


// 終了処理
void InputHandler::HandleRelease(uint32_t input)
{
	if (commandMap_.find(std::tolower(input)) != commandMap_.end())
	{
		commandMap_[std::tolower(input)]->Release();
	}
}


// コマンドの登録
void InputHandler::RegisterCommand(uint32_t input, ICommand* command)
{
	commandMap_[input] = command;
}

