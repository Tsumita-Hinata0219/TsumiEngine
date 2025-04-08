#include "DevActor.h"

DevActor::DevActor()
{
	IActor::Create("DevActor");
}

void DevActor::Init()
{
	IActor::AddRenderComponent(std::make_shared<DevRenderComponent>());
}

void DevActor::UpdateActor(float deltaTime)
{
	deltaTime;
}
