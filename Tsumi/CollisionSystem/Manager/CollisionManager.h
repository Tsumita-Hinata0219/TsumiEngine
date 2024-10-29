#pragma once

#include "../Collider/ColliderConfig.h"
#include "../IsCollision/IsCollision.h"
#include "../Event/CollisionEvent.h"
#include "../ColEventManager/ColEventManager.h"

#include "Math/MyMath.h"
#include "Math/Struct.h"
#include "GameObject/IObject/IObject.h"

#include <list>
#include <vector>

// 前方宣言
class CollisionComponent;
class CollisionShape;


/* CollisionManagerクラス */
class CollisionManager {

private: // シングルトン

	// コンストラクタ、デストラクタ
	CollisionManager() = default;
	~CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	const CollisionManager& operator=(const CollisionManager&) = delete;


public:

	// インスタンス取得
	static CollisionManager* GetInstance() {
		static CollisionManager instance;
		return &instance;
	}

	// 解放処理
	static void Finalize();

	// コライダーの登録
	void Register(uint32_t attribute, CollisionShape* shape);

	// 登録されているShapeを削除する
	void UnRegister(CollisionShape* shape);

	// 更新処理
	void Update();


#pragma region Accessor アクセッサ


#pragma endregion 


private:

	// コリジョン判定を行う
	void CheckCollisions();

	// 無効なポインタは削除
	void CheckAndCleanPointers();

	// ImGuiの描画
	void DrawImGui();


private:

	// コライダーのポインタ配列
	//std::vector<CollisionShape*> shapes_;
	std::map<uint32_t, std::list<CollisionShape*>> shapes_;

};
