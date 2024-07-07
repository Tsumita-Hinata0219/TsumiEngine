#pragma once

#include <sstream>

#include "../../BufferResource/BufferResource.h"

#include "../../../Project/Math/MyMath.h"
#include "../../../Project/Math/Struct.h"

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
	Vector4 color{};
};

/* GaussianFilter用 */
struct GaussianFilterMtl {
	Vector4 color{};
};

/* Grain用 */
struct GrainMtl {
	Vector4 color{};
};

/* GrayScale用 */
struct GrayScaleMtl {
	Vector4 color{};
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
};

/* SepiaTone用 */
struct SepiaToneMtl {
	Vector4 color{};
};

/* Vignetting用 */
struct VignettingMtl {
	Vector4 color{};
};
