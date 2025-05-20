#include "ConstantField.h"



/// <summary>
/// Fieldデータの取得
/// </summary>
void GpuField::ConstantField::Load_FieldData_From_Lua(const LuaScript& lua)
{
	GpuField::Data::ConstantField result;

	result.acceleration = lua.GetVariable<Vector3>("");
	result.damping = lua.GetVariable<float>("");
	result.angularVelocity = lua.GetVariable<Vector3>("");
	result.drag = lua.GetVariable<float>("");
	result.force = lua.GetVariable<Vector3>("");
	result.mass = lua.GetVariable<float>("");
	result.isUse = lua.GetVariable<int>("");

	*fieldData_ = result;
}
