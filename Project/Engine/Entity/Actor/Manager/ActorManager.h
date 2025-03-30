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
		actors_[actor->Get_Name()] = actor;
	}

	/// <summary>
	/// Actorの更新処理
	/// </summary>
	void UpdateActors() {
		float deltaTime = 1.0f / 60.0f;
		for (auto& actor : actors_) {
			actor.second->Update(deltaTime);
		}
	}

	/// <summary>
	/// 描画処理
	/// </summary>
	void RenderActors() {
		for (auto& actor : actors_) {
			actor.second->Render();
		}
	}

	/// <summary>
	/// 名前によるActorの取得
	/// </summary>
	std::shared_ptr<IActor> Get_ActorByName(const std::string& name) {
		auto it = actors_.find(name);
		if (it != actors_.end()) {
			return it->second;
		}
		return nullptr; // 見つからなければnullptr
	}

	/// <summary>
	/// 特定のActorの状態を設定
	/// </summary>
	void Set_ActorState(const std::string& name, IActor::State state) {
		auto actor = Get_ActorByName(name);
		if (actor) {
			actor->Set_State(state);
		}
	}

	/// <summary>
	/// すべてのActorの状態を設定
	/// </summary>
	void Set_AllActorState(IActor::State state) {
		for (auto& actor : actors_) {
			actor.second->Set_State(state);
		}
	}


private:

	std::unordered_map<std::string, std::shared_ptr<IActor>> actors_;

};
