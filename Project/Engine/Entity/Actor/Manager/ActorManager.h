#pragma once

#include "Math/MyMath.h"
#include "../Interface/IActor.h"


/* Actorの一元管理クラス */
class ActorManager {

private: // シングルトン

	// コンストラクタ、デストラクタ
	ActorManager() = default;
	~ActorManager() = default;
	ActorManager(const ActorManager&) = delete;
	const ActorManager& operator=(const ActorManager&) = delete;

public:

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	static ActorManager* GetInstance() {
		static ActorManager instance;
		return &instance;
	}

	/// <summary>
	/// Actorの追加処理
	/// </summary>
	void AddActor(std::shared_ptr<IActor> actor) {
		actorMap_[actor->GetName()] = actor;
	}

	/// <summary>
	/// Actorの更新処理
	/// </summary>
	void UpdateActors() {
		float deltaTime = 1.0f / 60.0f;
		for (auto& actor : actorMap_) {
			actor.second->Update(deltaTime);
		}
	}

	/// <summary>
	/// 描画処理
	/// </summary>
	void RenderActors() {
		for (auto& actor : actorMap_) {
			actor.second->Render();
		}
	}

	/// <summary>
	/// 名前によるActorの取得
	/// </summary>
	std::shared_ptr<IActor> Get_ActorByName(const std::string& name) {
		auto it = actorMap_.find(name);
		if (it != actorMap_.end()) {
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
			actor->SetState(state);
		}
	}

	/// <summary>
	/// すべてのActorの状態を設定
	/// </summary>
	void Set_AllActorState(IActor::State state) {
		for (auto& actor : actorMap_) {
			actor.second->SetState(state);
		}
	}

	/// <summary>
	/// actorMap_のクリア
	/// </summary>
	void Clear() {
		actorMap_.clear();
	}


private:

	std::unordered_map<std::string, std::shared_ptr<IActor>> actorMap_;

};
