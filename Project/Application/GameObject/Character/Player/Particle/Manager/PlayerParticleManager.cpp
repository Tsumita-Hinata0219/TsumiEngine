#include "PlayerParticleManager.h"



/// <summary>
/// 初期化処理
/// </summary>
void PlayerParticleManager::Init()
{
}


/// <summary>
/// 更新処理
/// </summary>
void PlayerParticleManager::Update()
{
	// MovementParticle
	for (std::list<PlayerMovementParticle>::iterator itr = movementParticles_.begin();
		itr != movementParticles_.end(); ++itr) {
		itr->Update();
	}


}


/// <summary>
/// 描画処理
/// </summary>
void PlayerParticleManager::Draw()
{
	// MovementParticle
	for (std::list<PlayerMovementParticle>::iterator itr = movementParticles_.begin();
		itr != movementParticles_.end(); ++itr) {
		itr->Draw3D();
	}
}
