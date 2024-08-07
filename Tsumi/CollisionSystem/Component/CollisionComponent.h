#pragma once

#include "../../Project/Math/MyMath.h"
#include "../Shape/CollisionShape.h"

#include <memory>


/* コリジョンシェイプを保持するクラス */
class CollisionComponent {

public:

	// コンストラクタ
	CollisionComponent(std::unique_ptr<CollisionShape> shape) {
		shape_ = std::move(shape);
	}


#pragma region Accessor

	// コリジョンシェイプ
	const CollisionShape* GetShape() const { return this->shape_.get(); }
	void SetShape(std::unique_ptr<CollisionShape> shape) { shape = std::move(shape); }

#pragma endregion 


private:

	// コリジョンシェイプ
	std::unique_ptr<CollisionShape> shape_;
};

