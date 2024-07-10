#include "IEnemySpawnState.h"
#include "../../Enemy/Enemy.h"


// 初期化処理
void IEnemySpawnState::Init(Enemy* enemy)
{
	// Enemyの設定
	enemy_ = enemy;

	// スケールのイージングにかかる時間の設定
	scaleEaseTime_.Start(0.0f, 60.0f);
}


// 更新処理
void IEnemySpawnState::Update()
{
	// SRTの取得
	srt_ = enemy_->GetSRT();


	// スケールをイージングにかける
	OutElasticScale();


	// SRTの再設定
	enemy_->SetSRT(srt_);
}


// 終了処理
void IEnemySpawnState::Exit()
{
}


// スケールをイージングにかける
void IEnemySpawnState::OutElasticScale()
{
	// タイマーの更新
	scaleEaseTime_.Update();

}
