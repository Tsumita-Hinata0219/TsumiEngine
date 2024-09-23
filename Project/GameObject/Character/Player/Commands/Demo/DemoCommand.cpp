#include "DemoCommand.h"
#include "../../Player.h"


// コンストラクタ
DemoCommand::DemoCommand(Player* player)
{
	this->player_ = player;
}


// 実行
void DemoCommand::Execute()
{
	player_->DemoCommandExe();
}


// 終了
void DemoCommand::Release()
{
	player_->DemoCommandRel();
}
