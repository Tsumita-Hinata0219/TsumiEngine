#pragma once

#include <list>
#include <memory>

#include "../../../IObject/IObject.h"
#include "../../../GameObject.h"


// 前方宣言
class BoxManager;
struct SRTN;

// Boxのタイプ
enum class BoxType {
	Barrier,
	Destructible,
};


/* Boxの基底クラス */
class IBoxObject : public IObject {

public:

	/// <summary>
	/// 仮想デストラク
	/// </summary>
	virtual ~IBoxObject() = default;


#pragma region Accessor アクセッサ

	// Manager
	virtual void SetManager(BoxManager* setManager) { this->manager_ = setManager; }

	// IsDead
	bool IsDead() const { return this->isDead_; }

	// SRT
	virtual void SetSRT(const SRTN& setSRT) = 0;

	// Scale
	virtual void SetScale(const Vector3& setScale) = 0;

	// Rotate
	virtual void SetRotate(const Vector3& setRotate) = 0;

	// Translate
	virtual void SetTranslate(const Vector3& setTranslate) = 0;

#pragma endregion 


protected:

	// マネージャー
	BoxManager* manager_ = nullptr;

	// HP
	int HP_ = 0;

	// 死亡フラグ
	bool isDead_ = false;

};