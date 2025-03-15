#include "SphereEmitter.h"


/// <summary>
/// Emitのデータの取得
/// </summary>
Emitter::SphereEmit SphereEmitter::LoadEmitData(const std::weak_ptr<LuaScript>& lScript)
{
    Emitter::SphereEmit result;

    result.translate = lScript.lock()->GetVariable<Vector4>("translate");
    result.radius = lScript.lock()->GetVariable<Vector4>("radius");

    return result;
}

