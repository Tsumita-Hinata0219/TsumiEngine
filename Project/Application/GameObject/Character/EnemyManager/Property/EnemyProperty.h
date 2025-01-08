#pragma once

#include <memory>
#include <functional>
#include <random>

#include "../Bullet/EnemyBullet.h"

#include "../../../GameObject.h"


namespace enemy {


	enum class ShotDirection {
		None,
		Forward,
		TripleForward,
		Cross,
		Omni_Four,
		Omni_Five,
		Omni_Eight,
		Random,
	};

	enum class BulletBehavior {
		None,
		Common,
		Resistant,
		Random,
	};

	enum class MovementBehavior {
		None,
		Static,
		Follow,
		Horizontal,
		Circular,
	};

	struct ShotFuncData {
		ShotDirection direction;
		BulletBehavior behavior;
		float shotInterval = 0.0f;
	};
	struct MovementFuncData {
		MovementBehavior behavior;
		bool isTilt_ = false;
		float velocity_ = 0.0f;
		Vector3 horizontalStart{};
		Vector3 horizontalEnd{};
		Vector3 horizontalMiddle{};
		Vector3 circular_Center{};
	};

}