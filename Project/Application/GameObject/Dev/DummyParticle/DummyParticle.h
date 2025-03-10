#pragma once

#include "GameObject/GameObject.h"



class DummyParticle
{
private:
	std::unique_ptr<SphereEmitter> sEmit_;

public:

	DummyParticle() = default;
	~DummyParticle() = default;

	void Init()
	{
		sEmit_ = std::make_unique<SphereEmitter>();
		sEmit_->Create();

		// Emitter
		if (auto lockedData = sEmit_->GetWeak_EmitData().lock()) {
			lockedData->translate = Vector4::zero;
			lockedData->radius = Vector4{ 2.0f, 2.0f, 2.0f, 0.0f };
		}
		// Range
		if (auto lockedData = sEmit_->GetWeak_RangeData().lock()) {
			// Scale
			lockedData->scaleMin = { 0.25f, 0.25f, 0.25f, 0.0f };
			lockedData->scaleMax = { 0.25f, 0.25f, 0.25f, 0.0f };
			// Rotate
			lockedData->rotateMin = { 0.0f, 0.0f, 0.0f, 0.0f };
			lockedData->rotateMax = { 0.0f, 0.0f, 0.0f, 0.0f };
			// Color
			lockedData->colorMin = { 0.0f, 0.0f, 0.0f, 1.0f };
			lockedData->colorMax = { 1.0f, 1.0f, 1.0f, 1.0f };
			// Velocity
			lockedData->velocityMin = { -0.3f, 0.0f, -0.3f, 0.0f };
			lockedData->velocityMax = { 0.3f, 1.0f, 0.3f, 0.0f };
			// Life
			lockedData->baseLifeTime = { 0.5f * 60.0f };
			lockedData->lifeTimeMin = { 0 };
			lockedData->lifeTimeMax = { 0 };
		}
		// Config
		if (auto lockedData = sEmit_->GetWeak_ConfigData().lock()) {
			lockedData->spawnInterval = { 0.1f };
			lockedData->elapsedTime = lockedData->spawnInterval;
			lockedData->spawnCount = { 250 };
			lockedData->isEmitting = false;
		}
	}

	void Update()
	{
		sEmit_->Update();
	}

	void Draw()
	{
		sEmit_->Draw3D();
	}

private:

};
