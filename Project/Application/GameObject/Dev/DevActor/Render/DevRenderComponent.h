#pragma once

#include "Entity/Entity.h"


class DevRenderComponent : public IRenderComponent {

public:

	DevRenderComponent() = default;
	~DevRenderComponent() = default;

	void Update() override;

private:

};
