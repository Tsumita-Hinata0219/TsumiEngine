#pragma once

#include "Math/MyMath.h"
#include "GameObject/GameObject.h"

#include "GameObject/Character/EnemyManager/ExecuteShot/EnemyExecuteShot.h"


/* JsonからよみとるPlayerのデータ */
struct EntityPlayerData {

};

/* JsonからよみとるEnemyのデータ */
struct EntityEnemyData {
	EnemyExecuteShot::Direction direction;
	EnemyExecuteShot::BulletBehavior behavior;
	float shotInterval = 0.0f;
};

/* JsonからよみとるEntityData */
struct EntityData {
	std::string type;
	std::string entityName;
	SRT srt{};
	EntityPlayerData playerData{};
	EntityEnemyData enemyData{};
	std::map<std::string, std::unique_ptr<EntityData>> children;
};

