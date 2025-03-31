#pragma once

#include "Entity/Entity.h"


class DevRenderComponent : public IRenderComponent
{
public:

	DevRenderComponent();
	~DevRenderComponent();

	void Create() override;
	void Update() override;

private:

};

DevRenderComponent::DevRenderComponent()
{
}

DevRenderComponent::~DevRenderComponent()
{
}

inline void DevRenderComponent::Create()
{
}

inline void DevRenderComponent::Update()
{
}
