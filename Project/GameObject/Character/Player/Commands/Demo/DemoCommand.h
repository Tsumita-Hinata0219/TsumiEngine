#pragma once

#include "../../../Tsumi/Command/ICommand.h"

class Player;

/* デモコマンドクラス */
class DemoCommand : public ICommand {

public:

	// コンストラクタ
	DemoCommand(Player* player);

	// 実行
	void Execute() override;

	// 終了
	void Release() override;


private:

	Player* player_ = nullptr;
};

