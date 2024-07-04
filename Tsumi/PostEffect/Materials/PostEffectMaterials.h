#pragma once

#include "../../BufferResource/BufferResource.h"

#include "../../../Project/Math/MyMath.h"
#include "../../../Project/Math/Struct.h"



/* 基底構造体 */
template<typename T>
struct PostEffectMtl {
	T data_{};
	bool enableEffect_ = true; // 使用フラグ
};


/* PostEffectに使用するMaterial */
/* BoxFilter用 */
struct BoxFilterMtl {

};

/* ColorGrading用 */
struct ColorGradingMtl {

};

/* Dissolve用 */
struct DissolveMtl {

};

/* GaussianFilter用 */
struct GaussianFilterMtl {

};

/* Grain用 */
struct GrainMtl {

};

/* GrayScale用 */
struct GrayScaleMtl {

};

/* OutLine用 */
struct OutLineMtl {


};

/* RadialBlur用 */
struct RadialBlurMtl {

};

/* Random用 */
struct RandomMtl {

};

/* SepiaTone用 */
struct SepiaToneMtl {


};

/* Vignetting用 */
struct VignettingMtl {


};
