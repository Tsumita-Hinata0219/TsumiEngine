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

	void DrawImGui(std::string label = "") {
		ImGui::ColorEdit4((label + "_color").c_str(), &color.x);
	}
};

/* ColorGrading用 */
struct ColorGradingMtl {
	Vector4 color{};

	void DrawImGui(std::string label = "") {
		ImGui::ColorEdit4((label + "_color").c_str(), &color.x);
	}
};

/* Dissolve用 */
struct DissolveMtl {
	Vector4 color = Vector4::one;
	float threshold = 0.0f;
	float thinkness = 0.0f;
	uint32_t maskTexture = 0;

	void DrawImGui(std::string label = "") {
		ImGui::ColorEdit4((label + "_color").c_str(), &color.x);
		ImGui::DragFloat((label + "_threshold").c_str(), &threshold, 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat((label + "_thinkness").c_str(), &thinkness, 0.01f, 0.0f, 1.0f);
	}
};

/* GaussianFilter用 */
struct GaussianFilterMtl {
	Vector4 color{};

	void DrawImGui(std::string label = "") {
		ImGui::ColorEdit4((label + "_color").c_str(), &color.x);
	}
};

/* Grain用 */
struct GrainMtl {
	Vector4 color{};
	float grainAmount = 0.0f;
	Vector2 noiseFactors = Vector2::zero;

	void DrawImGui(std::string label = "") {
		ImGui::ColorEdit4((label + "_color").c_str(), &color.x);
		ImGui::DragFloat((label + "_grainAmount").c_str(), &grainAmount, 0.01f);
		ImGui::DragFloat2((label + "_noiseFactors").c_str(), &noiseFactors.x);
	}
};

/* GrayScale用 */
struct GrayScaleMtl {
	Vector4 color{};

	void DrawImGui(std::string label = "") {
		ImGui::ColorEdit4((label + "_color").c_str(), &color.x);
	}
};

/* HSV用 */
struct HSVMtl {
	Vector4 color{};
	float hue = 0.0f;
	float saturation = 0.0f;
	float value = 0.0f;

	void DrawImGui(std::string label = "") {
		ImGui::ColorEdit4((label + "_color").c_str(), &color.x);
		ImGui::DragFloat((label + "_hue").c_str(), &hue, 0.01f);
		ImGui::DragFloat((label + "_saturation").c_str(), &saturation, 0.01f);
		ImGui::DragFloat((label + "_value").c_str(), &value, 0.01f);
	}
};

/* OutLine用 */
struct LuminanceOutLineMtl {
	Vector4 color{};

	void DrawImGui(std::string label = "") {
		ImGui::ColorEdit4((label + "_color").c_str(), &color.x);
	}
};
struct DepthOutLine {
	Vector4 color{};

	void DrawImGui(std::string label = "") {
		ImGui::ColorEdit4((label + "_color").c_str(), &color.x);
	}
};

/* RadialBlur用 */
struct RadialBlurMtl {
	Vector4 color{};

	void DrawImGui(std::string label = "") {
		ImGui::ColorEdit4((label + "_color").c_str(), &color.x);
	}
};

/* Random用 */
struct RandomMtl {
	Vector4 color{};
	float time = 0.0f;

	void DrawImGui(std::string label = "") {
		ImGui::ColorEdit4((label + "_color").c_str(), &color.x);
		ImGui::DragFloat((label + "_time").c_str(), &time, 0.01f);
	}
};

/* RetroCRT用 */
struct RetroCRTMtl {
	Vector4 color;            // エッジカラー
	float threshold;         // マスクの閾値
	float thinkness;         // エッジの厚さ
	float scanlineStrength;  // スキャンラインの強度
	int scanlineActive;     // スキャンラインの有効フラグ
	float chromaIntensity;   // 色収差の強度
	int chromaActive;       // 色収差の有効フラグ
	float barrelDistortion;  // バレル歪みの強度
	int barrelActive;       // バレル歪みの有効フラグ
	float noiseStrength;     // ノイズの強度
	int noiseActive;        // ノイズの有効フラグ
	float bloomStrength;     // ブルームの強度
	int bloomActive;        // ブルームの有効フラグ
	Vector2 resolution;       // ウィンドウサイズ
	float time;             // ゲーム開始時からのタイマー
	uint32_t maskTexture = 0; // マスク画像

	void DrawImGui(std::string label = "") {
		ImGui::ColorEdit4((label + "_color").c_str(), &color.x);
		ImGui::DragFloat((label + "_threshold").c_str(), &threshold);
		ImGui::DragFloat((label + "_thinkness").c_str(), &thinkness);
		ImGui::DragFloat((label + "_scanlineStrength").c_str(), &scanlineStrength);
		ImGui::RadioButton((label + "_scanlineDisabled").c_str(), &scanlineActive, 0); ImGui::SameLine();
		ImGui::RadioButton((label + "_scanlineEnabled").c_str(), &scanlineActive, 1);
		ImGui::DragFloat((label + "_chromaIntensity").c_str(), &chromaIntensity);
		ImGui::RadioButton((label + "_chromaDisabled").c_str(), &chromaActive, 0); ImGui::SameLine();
		ImGui::RadioButton((label + "_chromaEnabled").c_str(), &chromaActive, 1);
		ImGui::DragFloat((label + "_barrelDistortion").c_str(), &barrelDistortion);
		ImGui::RadioButton((label + "_barrelDisabled").c_str(), &barrelActive, 0); ImGui::SameLine();
		ImGui::RadioButton((label + "_barrelEnabled").c_str(), &barrelActive, 1);
		ImGui::DragFloat((label + "_noiseStrength").c_str(), &noiseStrength);
		ImGui::RadioButton((label + "_noiseDisabled").c_str(), &noiseActive, 0); ImGui::SameLine();
		ImGui::RadioButton((label + "_noiseEnabled").c_str(), &noiseActive, 1);
		ImGui::DragFloat((label + "_bloomStrength").c_str(), &bloomStrength);
		ImGui::RadioButton((label + "_bloomDisabled").c_str(), &bloomActive, 0); ImGui::SameLine();
		ImGui::RadioButton((label + "_bloomEnabled").c_str(), &bloomActive, 1);
		ImGui::DragFloat2((label + "_resolution").c_str(), &resolution.x, 0.0f);
		ImGui::DragFloat((label + "_time").c_str(), &time, 0.0f);
	}
};

/* SepiaTone用 */
struct SepiaToneMtl {
	Vector4 color{};

	void DrawImGui(std::string label = "") {
		ImGui::ColorEdit4((label + "_color").c_str(), &color.x);
	}
};

/* Vignetting用 */
struct VignettingMtl {
	Vector4 color = Vector4::one;
	float intensity = 0;
	float center = 0.5f;
	Vector2 radius = Vector2::one / 2.0f;
	float smoothness = 0.01f;
	float roundness = 1.0f;

	void DrawImGui(std::string label = "") {
		ImGui::ColorEdit4((label + "_color").c_str(), &color.x);
		ImGui::DragFloat((label + "_intensity").c_str(), &intensity);
		ImGui::DragFloat((label + "_center").c_str(), &center);
		ImGui::DragFloat2((label + "_radius").c_str(), &radius.x);
		ImGui::DragFloat((label + "_smoothness").c_str(), &smoothness);
		ImGui::DragFloat((label + "_roundness").c_str(), &roundness);
	}
};
