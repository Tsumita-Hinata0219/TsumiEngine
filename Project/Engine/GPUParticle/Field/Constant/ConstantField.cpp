#include "ConstantField.h"



/// <summary>
/// Fieldデータの取得
/// </summary>
GpuField::Data::ConstantField GpuField::ConstantField::LoadFieldData(const std::weak_ptr<LuaScript>& lScript)
{
    GpuField::Data::ConstantField result;

    result.acceleration = lScript.lock()->GetVariable<Vector3>("");
    result.damping = lScript.lock()->GetVariable<float>("");
    result.angularVelocity = lScript.lock()->GetVariable<Vector3>("");
    result.drag = lScript.lock()->GetVariable<float>("");
    result.force = lScript.lock()->GetVariable<Vector3>("");
    result.mass = lScript.lock()->GetVariable<float>("");
    result.isUse = lScript.lock()->GetVariable<int>("");

    return result;
}
