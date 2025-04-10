#pragma once

#include "Entity/Entity.h"

#include "Comp/Move/DevActorMoveComponent.h"
#include "Rend/DevRenderComponent.h"

class DevActor : public IActor {

private:


public:

	DevActor();
	~DevActor() = default;

	void Init() override;
	void UpdateActor(float deltaTime) override;

};

