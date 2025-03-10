#pragma once

#include "../Interface/IEmitter.h"


class SphereEmitter : public IEmitter<Emitter::SphereEmit> {

public:

	/// <summary>
	/// コンストラク
	/// </summary>
	SphereEmitter() 
	{
		pipeLine_Category = PipeLine::Category::SphereEmitter;
	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SphereEmitter() = default;


private:

};
