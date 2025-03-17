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
	void UpdateActors() {
		float deltaTime = 1.0f / 60.0f;
		for (auto& actor : actors_) {
			actor->Update(deltaTime);
		}
	}


	/// <summary>
	/// 描画処理
	/// </summary>
	void RenderActors() {
		for (auto& actor : actors_) {
			actor->Render();
		}
	}


private:

	std::vector<std::shared_ptr<IActor>> actors_;

};
