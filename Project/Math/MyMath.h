#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "MathQuaternion.h"
#include "MathOperations.h"
#include "MathFunction.h"
#include "CollisionStructures.h"



#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <array>
#include <numbers>


namespace Math {
	constexpr float PI = 3.1415926535897932384626433832795028f;
	constexpr float Double_PI = PI * 2;
	constexpr float Half_PI = PI * 0.5f;
}

