#include "SphereEmitter.h"


/// <summary>
/// LuaScriptからEmitterデータの読み込み
/// </summary>
Emitter::Data::SphereEmit Emitter::SphereEmitter::Load_EmitData_From_Lua(const std::weak_ptr<LuaScript>& lua)
{
	Emitter::Data::SphereEmit result;

	if (auto lockedData = lua.lock()) {

		result.translate = lockedData->GetVariable<Vector4>("SphereEmitter.translate");
		result.radius = lockedData->GetVariable<Vector4>("SphereEmitter.radius");
	}

	return result;
}
