#pragma once

#include "Math/MyMath.h"
#include "GameObject/GameObject.h"


/* JsonからよみとるEntityData */
struct EntityData {
	std::string type;
	std::string entityName;
	SRT srt{};
	std::map<std::string, std::unique_ptr<EntityData>> children;
};

