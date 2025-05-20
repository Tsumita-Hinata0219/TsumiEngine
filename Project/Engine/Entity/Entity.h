#pragma once

#include "Math/MyMath.h"

#include "Entity/Actor/Interface/IActor.h"
#include "Entity/Component/Base/IBaseComponent.h"
#include "Entity/Component/Collision/ICollisionComponent.h"
#include "Entity/Component/Render/IRenderComponent.h"

#include "Lua/Script/LuaScript.h"

#include "FlagManager/FlagManager.h"
#include "3D/Model/Model.h"
#include "2D/Sprite/Sprite.h"
#include "TextureManager/TextureManager.h"
#include "Audio/Audio.h"
#include "Input/Input.h"

#include "GPUParticle/Particle/GPUParticle.h"
#include "GPUParticle/Field/ParticleField.h"
#include "GPUParticle/Field/Constant/ConstantField.h"
#include "GPUParticle/Emitter/Sphere/SphereEmitter.h"

#include "Utilities/ImGuiManager/ImGuiManager.h"
#include "Utilities/ObjectPool/ObjectPool.h"
#include "Utilities/RandomGenerator/RandomGenerator.h"
#include "Utilities/TextLog/TextLog.h"
#include "Utilities/Timer/Timer.h"
#include "Utilities/EnumUtilities/EnumUtilities.h"
#include "Utilities/PtrUtilities/PtrUtilities.h"

#include "Camera/Manager/CameraManager.h"