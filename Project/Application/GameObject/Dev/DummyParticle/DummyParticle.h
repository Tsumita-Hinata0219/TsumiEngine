#pragma once

#include "GameObject/GameObject.h"



class DummyParticle {

public:

	DummyParticle();
	~DummyParticle() = default;

	void Init();
	void Update();
	void Draw();

	void ReLoad_EmitData();
	void ReLoad_RangeData();
	void ReLoad_ComfigData();
	void ReLoad_FieldData();

private:
	// パーティクルに必要なもの
	std::unique_ptr<Emitter::SphereEmitter> sEmit_;
	std::weak_ptr<Emitter::Data::SphereEmit> sEmitData_;
	std::unique_ptr<GpuField::ConstantField> cField_;

	// Luaスクリプト
	std::weak_ptr<LuaScript> sEmitLua_;
	std::weak_ptr<LuaScript> rangeLua_;
	std::weak_ptr<LuaScript> configLua_;
	std::weak_ptr<LuaScript> cFieldLua_;
	std::weak_ptr<LuaScript> movementLua_;

	// 確認用
	std::unique_ptr<Model> model_;
	ModelManager* modelManager_ = nullptr;
	Transform trans_{};
};
