#pragma once

#include "../Interface/IParticleField.h"


class ConstantField : public IParticleField<GpuField::ConstantField> {

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
	GpuField::ConstantField LoadFieldData(const std::weak_ptr<LuaScript>& lScript) override;

private:

};