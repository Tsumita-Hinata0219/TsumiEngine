#pragma once

#include "Entity/Entity.h"


class DevRenderComponent : public IRenderComponent
{
public:

	DevRenderComponent() = default;
	~DevRenderComponent() = default;

	void Create() override;
	void Update() override;

private:

};

inline void DevRenderComponent::Create()
{
	renderState_->SetRenderData("Dev");
}

inline void DevRenderComponent::Update()
{
}
