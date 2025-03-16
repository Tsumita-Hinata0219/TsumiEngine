#include "ConstantField.h"



/// <summary>
/// Fieldデータの取得
/// </summary>
void GpuField::ConstantField::Load_FieldData_From_Lua(const std::weak_ptr<LuaScript>& lScript)
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

    *fieldData_ = result;
}
