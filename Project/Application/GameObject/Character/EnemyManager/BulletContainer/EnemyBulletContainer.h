//#pragma once
//
//#include "GameObject/GameObject.h"
//#include "../Property/EnemyProperty.h"
//#include "../Bullet/EnemyBullet.h"
////#include "ShotPattern/IEnemyShotPattern.h"
////#include "ShotFactory/EnemyShotStateFactory.h"
//
//
//
//// 前方宣言
//class IEnemy;
//
//
///* Enemyそれぞれが持つ、Bulletの管理クラス */
//class EnemyBulletContainer {
//
//public:
//
//	/// <summary>
//	/// コンストラクタ
//	/// </summary>
//	EnemyBulletContainer();
//
//	/// <summary>
//	/// デストラクタ
//	/// </summary>
//	~EnemyBulletContainer() = default;
//
//	/// <summary>
//	/// 初期化処理
//	/// </summary>
//	void Init(enemy::ShotFuncData data);
//
//	/// <summary>
//	/// 更新処理
//	/// </summary>
//	void Update();
//
//	/// <summary>
//	/// 描画処理
//	/// </summary>
//	void Draw();
//
//
//#pragma region Accessor アクセッサ
//
//	// 親エネミー
//	void SetOwner(IEnemy* pEnemy) { this->owner_ = pEnemy; }
//
//#pragma endregion
//
//
//private:
//
//	/// <summary>
//	/// バレット追加
//	/// </summary>
//	void AddBulletInstance(Vector3 initPos, Vector3 initVel, bool isState);
//
//
//private:
//
//	// 親エネミー
//	IEnemy* owner_ = nullptr;
//
//	// BulletのPool
//	ObjectPool<EnemyBullet> bulletPool_;
//	// BulletのList配列
//	std::list<EnemyBullet*> bulletList_;
//
//	// 射撃タイマー
//	Timer shotTimer_{};
//
//	// 射撃クラス
//	//std::unique_ptr<IEnemyShotPattern> exeShot_;
//};