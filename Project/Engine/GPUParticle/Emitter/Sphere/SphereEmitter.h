#pragma once

#include "../Interface/IEmitter.h"


namespace Emitter {

class SphereEmitter : public IEmitter<Emitter::Data::SphereEmit> {

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

}