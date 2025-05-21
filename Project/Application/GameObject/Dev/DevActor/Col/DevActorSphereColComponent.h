#pragma once

#include "Entity/Entity.h"


class DevActorSphereColComponent: public IBaseComponent {

public:

	DevActorSphereColComponent();
	~DevActorSphereColComponent() = default;

	void Init() override;
	void Update(float deltaTime) override;


private:

	std::shared_ptr<Entity::Collision::CollisionSphere> sphereCol_;

};


inline DevActorSphereColComponent::DevActorSphereColComponent()
{
	sphereCol_ = std::make_shared<Entity::Collision::CollisionSphere>();
}

inline void DevActorSphereColComponent::Init()
{
	IBaseComponent::Create("DevActorSphereColComponent");
	sphereCol_->OnRegister();
}

inline void DevActorSphereColComponent::Update([[maybe_unused]]float deltaTime)
{


}