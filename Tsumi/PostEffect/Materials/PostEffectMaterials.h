#pragma once

#include <sstream>

#include "../../BufferResource/BufferResource.h"

#include "Math/MyMath.h"
#include "Math/Struct.h"

/* AbsentMtl */
struct AbsentMtl{};

/* BoxFilter用 */
struct BoxFilterMtl {
	Vector4 color{};
};

/* ColorGrading用 */
struct ColorGradingMtl {
	Vector4 color{};
};

/* Dissolve用 */
struct DissolveMtl {
	Vector4 color = Vector4::one;
	float threshold = 0.0f;
	float thinkness = 0.0f;
	uint32_t maskTexture = 0;
};

/* GaussianFilter用 */
struct GaussianFilterMtl {
	Vector4 color{};
};

/* Grain用 */
struct GrainMtl {
	Vector4 color{};
	float grainAmount = 0.0f;
	Vector2 noiseFactors = Vector2::zero;
};

/* GrayScale用 */
struct GrayScaleMtl {
	Vector4 color{};
};

/* HSV用 */
struct HSVMtl {
	Vector4 color{};
	float hue = 0.0f;
	float saturation = 0.0f;
	float value = 0.0f;
};

/* OutLine用 */
struct LuminanceOutLineMtl {
	Vector4 color{};
};
struct DepthOutLine {
	Vector4 color{};
};

/* RadialBlur用 */
struct RadialBlurMtl {
	Vector4 color{};
};

/* Random用 */
struct RandomMtl {
	Vector4 color{};
	float time = 0.0f;
};

/* SepiaTone用 */
struct SepiaToneMtl {
	Vector4 color{};
};

/* Vignetting用 */
struct VignettingMtl {
	Vector4 color = Vector4::one;
	float intensity = 0;
	float center = 0.5f;
	Vector2 radius = Vector2::one / 2.0f;
	float smoothness = 0.01f;
	float roundness = 1.0f;
};
