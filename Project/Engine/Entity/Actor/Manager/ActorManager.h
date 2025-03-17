#pragma once

#include "Math/MyMath.h"
#include "../Interface/IActor.h"


/* Actorの一元管理クラス */
class ActorManager {

public:

	/// <summary>
	/// Actorの追加処理
	/// </summary>
	void AddActor(std::shared_ptr<IActor> actor) {
		actors_.push_back(actor);
	}


	/// <summary>
	/// Actorの更新処理
	/// </summary>
	void UpdateActors(float deltaTime) {
		for (auto& actor : actors_) {
			actor->Update(deltaTime);
		}
	}


private:

	std::vector<std::shared_ptr<IActor>> actors_;

};
