#pragma once

#include "../Interface/IParticleField.h"


namespace GpuField {

class ConstantField : public IParticleField<GpuField::Data::ConstantField> {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ConstantField() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ConstantField() = default;

	/// <summary>
	/// Fieldデータの取得
	/// </summary>
	GpuField::Data::ConstantField LoadFieldData(const std::weak_ptr<LuaScript>& lScript) override;

private:

};
}