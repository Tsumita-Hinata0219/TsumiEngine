#include "DevActor.h"

DevActor::DevActor()
{
	IActor::Create("DevActor");
}

void DevActor::Init()
{
	IActor::AddComponent(std::make_shared<DevActorMoveComponent>());
	IActor::AddComponent(std::make_shared<DevRenderComponent>());

	transNode_.lock()->srt.scale = { 0.1f, 0.1f, 0.1f };
	transNode_.lock()->srt.translate = { 0.0f, 0.0f, 10.0f };

	//isRender_ = false;
}

void DevActor::UpdateActor(float deltaTime)
{
	deltaTime;
}
