#pragma once


// コマンドの基底クラス
class ICommand {

public:

	// 仮想デストラクタ
	virtual ~ICommand() {};

	// 実行関数 : 純粋仮想関数
	virtual void Execute() = 0;

	// 終了関数 : 純粋仮想関数
	virtual void Release() = 0;
};