#include "DevActor.h"

void DevActor::Init()
{
	IActor::Create("DevActor");
	IActor::AddRenderComponent(std::make_shared<DevRenderComponent>());
}

void DevActor::UpdateActor(float deltaTime)
{
	deltaTime;
}
