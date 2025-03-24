#pragma once

#include "Math/MyMath.h"


struct TransComponent {
	Vector3 scale{};
	Vector3 rotate{};
	Vector3 translate{};
	TransComponent() : 
		scale(1.0f, 1.0f, 1.0f), 
		rotate(0.0f, 0.0f, 0.0f), 
		translate(0.0f, 0.0f, 0.0f) {}
};