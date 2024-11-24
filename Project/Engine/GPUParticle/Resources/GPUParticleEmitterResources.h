#pragma once

#include "../../BufferResource/BufferResource.h"
#include "../../Transform/Transform.h"
#include "../../3D/Model/ModelStructure/ModelStructure.h"
#include "../Structure/GPUParticleEmitterStructure.h"


struct GPUParticleEmitterDatas {

	// エミッターのデータ
	Particle::Emit::SphereEmitter sphereEmitter{};

	// タイマー
	Particle::PerFrame perFrame{};

};

struct GPUParticleEmitterResouces {

	// エミッターのデータ
	BufferResource<Particle::Emit::SphereEmitter> sphereEmitter;

	// タイマー
	BufferResource<Particle::PerFrame> perFrame;
};