#pragma once

#include <memory>
#include <functional>
#include <random>

#include "../Bullet/EnemyBullet.h"

#include "../../../GameObject.h"


// 前方宣言
class EnemyManager;
class IEnemy;

/* エネミーの射撃処理 */
class EnemyExecuteShot {

public:

	enum class Direction {
		Forward,
		TripleForward,
		Cross,
		Omni_Four,
		Omni_Five,
		Omni_Eight,
		Random,
	};

	enum class BulletBehavior {
		Normal,
		Resistant,
		Random,
	};

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyExecuteShot(EnemyManager* manager, IEnemy* owner);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyExecuteShot() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init(Direction direction, BulletBehavior behavior);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


#pragma region Accessor アクセッサ

	// Timer
	void SetTimer(float interval) { this->shotTimer_.Init(0.0f, interval); }

#pragma endregion


private:

	/// <summary>
	/// 新しいバレットを追加
	/// </summary>
	void AddNewBullet(const Vector3& direction);

	/// <summary>
	/// 射撃関数の設定
	/// </summary>
	void SetShotFunc(Direction direction);

	/// <summary>
	/// 前方射撃
	/// </summary>
	void Shot_Forward();

	/// <summary>
	/// 3Way前方
	/// </summary>
	void Shot_TripleForward();

	/// <summary>
	/// 4Way対角線
	/// </summary>
	void Shot_Cross();

	/// <summary>
	/// 4Way全方位
	/// </summary>
	void Shot_Omni_Four();

	/// <summary>
	/// 5Way全方位
	/// </summary>
	void Shot_Omni_Five();

	/// <summary>
	/// 8Way全方位
	/// </summary>
	void Shot_Omni_Eight();

	/// <summary>
	/// ランダム
	/// </summary>
	void Shot_Random();


private:

	// バレットの速度
	const float kBulletSpeed_ = 0.25f;

	// 射撃処理のfunction
	std::function<void()> shotFunc_;

	// EnemyManager
	EnemyManager* manager_ = nullptr;

	// オーナーエネミー
	IEnemy* owner_ = nullptr;

	// バレット挙動
	BulletBehavior behavior_ = BulletBehavior::Normal;
	bool behabirState_ = false;

	// 射撃タイマー
	Timer shotTimer_{};

	std::mt19937 randEngine_; // ランダムエンジン
	std::uniform_int_distribution<> behabirDist_; // 0 or 1 の分布
	std::uniform_real_distribution<float> directionDist_; // -1 ~ +1 の分布
};
