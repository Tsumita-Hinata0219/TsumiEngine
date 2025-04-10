#pragma once

#include "Entity/Entity.h"


class DevActorMoveComponent : public IComponent
{
public:

	DevActorMoveComponent() = default;
	~DevActorMoveComponent() = default;

	void Init() override;
	void Update(float deltaTime) override;


private:

};


inline void DevActorMoveComponent::Init()
{
	IComponent::Create("DevActorMove");
}

inline void DevActorMoveComponent::Update(float deltaTime)
{
	deltaTime;
}