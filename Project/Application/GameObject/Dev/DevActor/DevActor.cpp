#include "DevActor.h"

DevActor::DevActor()
{
	IActor::Create("DevActor");
}

void DevActor::Init()
{
	IActor::AddComponent(std::make_shared<DevActorMoveComponent>());
	IActor::AddComponent(std::make_shared<DevRenderComponent>());
}

void DevActor::UpdateActor(float deltaTime)
{
	deltaTime;
}
