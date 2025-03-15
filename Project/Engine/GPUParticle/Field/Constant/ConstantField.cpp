#include "ConstantField.h"



/// <summary>
/// Fieldデータの取得
/// </summary>
GpuField::Data::ConstantField GpuField::ConstantField::LoadFieldData(const std::weak_ptr<LuaScript>& lScript)
{
    GpuField::Data::ConstantField result;

    if (auto lockedData = lScript.lock()) {

        result.acceleration = lockedData->GetVariable<Vector3>("");
        result.damping = lockedData->GetVariable<float>("");
        result.angularVelocity = lockedData->GetVariable<Vector3>("");
        result.drag = lockedData->GetVariable<float>("");
        result.force = lockedData->GetVariable<Vector3>("");
        result.mass = lockedData->GetVariable<float>("");
        result.isUse = lockedData->GetVariable<int>("");
    }

    return result;
}
