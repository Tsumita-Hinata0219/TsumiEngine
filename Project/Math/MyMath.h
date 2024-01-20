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

// 前後左右の構造体 V:Vertical H;Horizontal
struct VHInfo {

	float up, down, left, right;

	VHInfo() : up(0.0f), down(0.0f), left(0.0f), right(0.0f) {};
	VHInfo(float u, float d, float l, float r) : up(u), down(d), left(l), right(r) {};
};

// 範囲
struct Scope {
	Vector2 X;
	Vector2 Y;
	Vector2 Z;
};