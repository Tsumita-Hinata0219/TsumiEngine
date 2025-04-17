#pragma once

#include "Entity/Entity.h"


class DevActorSphereColComponent: public ICollisionComponent {

public:

	DevActorSphereColComponent() = default;
	~DevActorSphereColComponent() = default;

	void Init() override;
	void Update(float deltaTime) override;

	std::shared_ptr<Entity::Collision::IEntityCollider> GetCollider() const override{
		return sphereCol_;
	}


private:

	std::shared_ptr<Entity::Collision::SphereCollider> sphereCol_;

};


inline void DevActorSphereColComponent::Init()
{
	ICollisionComponent::Create("DevActorSphereComponent");
}

inline void DevActorSphereColComponent::Update(float deltaTime)
{
	deltaTime;
}