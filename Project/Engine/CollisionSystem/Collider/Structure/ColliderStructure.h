#pragma once

#include "Math/MyMath.h"

namespace Collider {

	struct Sphere {
		Vector3 center{};
		float radius = 0.0f;
	};

	struct AABB {
		Vector3 center{};
		Vector3 size{};
	};

	struct OBB {
		Vector3 center{};
		Vector3 rotate{};
		Vector3 orientations[3]{};
		Vector3 size{};
	};

	struct Segment {
		Vector3 origin{};
		Vector3 diff{};
	};
	
	struct Capsule {
		Vector3 center{};
		Segment segment{};
		Vector3 rotate{};
		float radius = 0.0f;
	};
}