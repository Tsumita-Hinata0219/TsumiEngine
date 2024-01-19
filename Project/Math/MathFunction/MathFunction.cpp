#include "MathFunction.h"



/// -------------------------------------------------------------------------
/// ログ
/// -------------------------------------------------------------------------
// string->wstring
std::wstring ConverString(const std::string& str) {
	if (str.empty())
	{
		return std::wstring();
	}

	auto sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&str[0]), static_cast<int>(str.size()), NULL, 0);
	if (sizeNeeded == 0)
	{
		return std::wstring();
	}
	std::wstring result(sizeNeeded, 0);
	MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(&str[0]), static_cast<int>(str.size()), &result[0], sizeNeeded);
	return result;
}
// wstring->string
std::string ConvertString(const std::wstring& str) {
	if (str.empty())
	{
		return std::string();
	}

	auto sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), NULL, 0, NULL, NULL);
	if (sizeNeeded == 0)
	{
		return std::string();
	}
	std::string result(sizeNeeded, 0);
	WideCharToMultiByte(CP_UTF8, 0, str.data(), static_cast<int>(str.size()), result.data(), sizeNeeded, NULL, NULL);
	return result;
}
// wstring->string
void Log(const std::string& message) {
	OutputDebugStringA(message.c_str());
}



/// -------------------------------------------------------------------------
/// 2次元ベクトル
/// -------------------------------------------------------------------------
// 内積
float Dot(const Vector2& v1, const Vector2& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y);
}

// 外積
float Cross(const Vector2& v1, const Vector2& v2) {
	return (v1.x * v2.y) - (v1.y * v2.x);
}

// 長さ
float Length(const Vector2& v) {
	return std::sqrt(Dot(v, v));
}

// 正規化
Vector2 Normalize(const Vector2& v) {
	return v * (1.0f / Length(v));
}

// 正射影ベクトル
Vector2 Project(const Vector2& v1, const Vector2& v2) {
	return Dot(v1, Normalize(v2)) * Normalize(v2);
}

// 線形補間
Vector2 Lerp(const Vector2& start, const Vector2& end, const float t) {
	return start + t * (end - start);
}




/// -------------------------------------------------------------------------
/// 3次元ベクトル
/// -------------------------------------------------------------------------
// 内積
float Dot(const Vector3& v1, const Vector3& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

// 外積
Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	return { (v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), (v1.x * v2.y) - (v1.y * v2.x) };
}

// 長さ
float Length(const Vector3& v) {
	return std::sqrt(Dot(v, v));
}

// 正規化
Vector3 Normalize(const Vector3& v) {
	return v * (1.0f / Length(v));
}

// 正射影ベクトル
Vector3 Project(const Vector3& v1, const Vector3& v2) {
	return Dot(v1, Normalize(v2)) * Normalize(v2);
}

// 線形補間
Vector3 Lerp(const Vector3& start, const Vector3& end, const float t) {
	return start + t * (end - start);
}

// 最近接線
Vector3 ClosestPoint(const Vector3& p, const Segment& s) {
	float length = Length(p);
	Vector3 normalize = Normalize(p);
	float dist = Dot((p - s.origin), normalize);
	dist = std::clamp(dist, 0.0f, length);
	Vector3 proj = dist * normalize;
	return s.origin + proj;
}

// 法線ベクトル
Vector3 Perpendicular(const Vector3& v) {
	if (v.x != 0.0f || v.y != 0.0f) {
		return { -v.y, v.x, 0.0f };
	}
	return { 0.0f, -v.z, v.y };
}

// 座標変換
Vector3 TransformByMatrix(const Vector3 v, const Matrix4x4 m)
{
	Vector3 result{};

	result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z *
		m.m[2][0] + 1.0f * m.m[3][0];

	result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z *
		m.m[2][1] + 1.0f * m.m[3][1];

	result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z *
		m.m[2][2] + 1.0f * m.m[3][2];

	float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z *
		m.m[2][3] + 1.0f * m.m[3][3];

	assert(w != 0.0f);

	result.x /= w;
	result.y /= w;
	result.z /= w;

	return  result;
}

// ベクトル変換
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m) {
	Vector3 result{};

	result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0];

	result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1];

	result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2];

	return result;
}




/// -------------------------------------------------------------------------
/// 3x3行列
/// -------------------------------------------------------------------------




/// -------------------------------------------------------------------------
/// 4x4行列
/// -------------------------------------------------------------------------
// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 result{};

	float as =
		m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] +
		m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] +
		m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2] -

		m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] -
		m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] -
		m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2] -

		m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] -
		m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] -
		m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2] +

		m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] +
		m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] +
		m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2] +

		m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] +
		m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] +
		m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2] -

		m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] -
		m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] -
		m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2] -

		m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] -
		m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] -
		m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0] +

		m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] +
		m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] +
		m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];

	assert(as != 0.0f);
	float determinantRecp = 1.0f / as;

	// 一行目
	result.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] +
		m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][3] * m.m[2][2] * m.m[3][1] -
		m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]) *
		determinantRecp;

	result.m[0][1] = (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] -
		m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[2][2] * m.m[3][1] +
		m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]) *
		determinantRecp;

	result.m[0][2] = (
		m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] +
		m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[3][1] -
		m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]) *
		determinantRecp;

	result.m[0][3] = (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] -
		m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] +
		m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]) *
		determinantRecp;


	// 二行目
	result.m[1][0] = (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] -
		m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][3] * m.m[2][2] * m.m[3][0] +
		m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]) *
		determinantRecp;

	result.m[1][1] = (
		m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] +
		m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[2][2] * m.m[3][0] -
		m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]) *
		determinantRecp;

	result.m[1][2] = (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] -
		m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[3][0] +
		m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]) *
		determinantRecp;

	result.m[1][3] = (
		m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] +
		m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] -
		m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]) *
		determinantRecp;


	// 三行目
	result.m[2][0] = (
		m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] +
		m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][3] * m.m[2][1] * m.m[3][0] -
		m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]) *
		determinantRecp;

	result.m[2][1] = (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] -
		m.m[0][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[2][1] * m.m[3][0] +
		m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]) *
		determinantRecp;

	result.m[2][2] = (
		m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] +
		m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][3] * m.m[1][1] * m.m[3][0] -
		m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]) *
		determinantRecp;

	result.m[2][3] = (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] -
		m.m[0][3] * m.m[1][0] * m.m[2][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] +
		m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]) *
		determinantRecp;


	// 四行目
	result.m[3][0] = (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] -
		m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[1][2] * m.m[2][1] * m.m[3][0] +
		m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]) *
		determinantRecp;

	result.m[3][1] = (

		m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] +
		m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[2][1] * m.m[3][0] -
		m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]) *
		determinantRecp;

	result.m[3][2] = (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] -
		m.m[0][2] * m.m[1][0] * m.m[3][1] + m.m[0][2] * m.m[1][1] * m.m[3][0] +
		m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]) *
		determinantRecp;

	result.m[3][3] = (

		m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] +
		m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] -
		m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]) *
		determinantRecp;

	return result;
}

// 転置行列
Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 result{};

	result.m[0][0] = m.m[0][0];
	result.m[0][1] = m.m[1][0];
	result.m[0][2] = m.m[2][0];
	result.m[0][3] = m.m[3][0];

	result.m[1][0] = m.m[0][1];
	result.m[1][1] = m.m[1][1];
	result.m[1][2] = m.m[2][1];
	result.m[1][3] = m.m[3][1];

	result.m[2][0] = m.m[0][2];
	result.m[2][1] = m.m[1][2];
	result.m[2][2] = m.m[2][2];
	result.m[2][3] = m.m[3][2];

	result.m[3][0] = m.m[0][3];
	result.m[3][1] = m.m[1][3];
	result.m[3][2] = m.m[2][3];
	result.m[3][3] = m.m[3][3];

	return result;
}

// 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3 translate) {
	Matrix4x4 result{};

	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;


	return result;
}

// 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3 scale) {
	Matrix4x4 result{};

	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;


	return result;
}

// 回転行列(X,Y,Z)
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result{};

	result.m[0][0] = 1;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = -std::sin(radian);
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}
Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result{};

	result.m[0][0] = std::cos(radian);
	result.m[0][1] = 0;
	result.m[0][2] = -std::sin(radian);
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = std::sin(radian);
	result.m[2][1] = 0;
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}
Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result{};

	result.m[0][0] = std::cos(radian);
	result.m[0][1] = std::sin(radian);
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = -std::sin(radian);
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}

// 回転行列(all)
Matrix4x4 MakeRotateXYZMatrix(float radianX, float radianY, float radianZ) {
	Matrix4x4 result{};

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(radianX);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(radianY);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(radianZ);

	result = rotateXMatrix * (rotateYMatrix * rotateZMatrix);

	return result;
}

// 3次元アフィン変換行列 (W = SRT)
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result{};

	// 拡大縮小行列
	Matrix4x4 scaleMatrix;
	scaleMatrix = MakeScaleMatrix(scale);

	// 回転行列(all)
	Matrix4x4 rotateMatrix;
	rotateMatrix = MakeRotateXYZMatrix(rotate.x, rotate.y, rotate.z);

	// 平行移動行列
	Matrix4x4 translateMatrix;
	translateMatrix = MakeTranslateMatrix(translate);

	result = scaleMatrix * (rotateMatrix * translateMatrix);

	return result;
}

// 透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspecrRatio, float nearClip, float farClip) {
	Matrix4x4 result{};

	result.m[0][0] = (1 / aspecrRatio) * 1 / std::tan(fovY / 2);
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1 / std::tan(fovY / 2);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = -nearClip * farClip / (farClip - nearClip);
	result.m[3][3] = 0.0f;

	return result;
}

// 正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {

	assert(left != right);
	assert(top != bottom);

	Matrix4x4 result{};

	result.m[0][0] = 2 / (right - left);
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 2 / (top - bottom);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1 / (farClip - nearClip);
	result.m[2][3] = 0.0f;

	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1.0f;

	return result;
}

// ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result{};

	result.m[0][0] = width / 2;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = -height / 2;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = maxDepth - minDepth;
	result.m[2][3] = 0.0f;

	result.m[3][0] = left + (width / 2);
	result.m[3][1] = top + (height / 2);
	result.m[3][2] = minDepth;
	result.m[3][3] = 1.0f;

	return result;
}

// 任意軸回転行列
Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle) {
	float cosTheta = cosf(angle);
	float sinTheta = sinf(angle);

	Matrix4x4 result{};
	result = Matrix4x4::identity;


	result.m[0][0] = (axis.x * axis.x) * (1 - cosTheta) + cosTheta;
	result.m[0][1] = (axis.x * axis.y) * (1 - cosTheta) - axis.z * sinTheta;
	result.m[0][2] = (axis.x * axis.z) * (1 - cosTheta) + axis.y * sinTheta;

	result.m[1][0] = (axis.x * axis.y) * (1 - cosTheta) + axis.z * sinTheta;
	result.m[1][1] = (axis.y * axis.y) * (1 - cosTheta) + cosTheta;
	result.m[1][2] = (axis.y * axis.z) * (1 - cosTheta) - axis.x * sinTheta;

	result.m[2][0] = (axis.x * axis.z) * (1 - cosTheta) - axis.y * sinTheta;
	result.m[2][1] = (axis.y * axis.z) * (1 - cosTheta) + axis.x * sinTheta;
	result.m[2][2] = (axis.z * axis.z) * (1 - cosTheta) + cosTheta;


	return result;
}
Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float cos, float sin) {
	Matrix4x4 result{};
	result = Matrix4x4::identity;


	result.m[0][0] = axis.x * axis.x * (1 - cos) + cos;
	result.m[0][1] = axis.x * axis.y * (1 - cos) - axis.z * sin;
	result.m[0][2] = axis.x * axis.z * (1 - cos) + axis.y * sin;

	result.m[1][0] = axis.x * axis.y * (1 - cos) + axis.z * sin;
	result.m[1][1] = axis.y * axis.y * (1 - cos) + cos;
	result.m[1][2] = axis.y * axis.z * (1 - cos) - axis.x * sin;

	result.m[2][0] = axis.x * axis.z * (1 - cos) - axis.y * sin;
	result.m[2][1] = axis.y * axis.z * (1 - cos) + axis.x * sin;
	result.m[2][2] = axis.z * axis.z * (1 - cos) + cos;
	return result;
}

// ある方向からある方向への回転
Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to) {

	Vector3 fromVector = Normalize(from);
	Vector3 toVector = Normalize(to);
	Vector3 n = Normalize(Cross(fromVector, toVector));

	float cos = Dot(fromVector, toVector);
	float sin = Length(Cross(fromVector, toVector));


	if (from.x == -to.x && from.y == -to.y && from.z == -to.z) {

		if (from.x != 0.0f || from.y != 0.0f) {

			n = { from.y, -from.x, 0.0f };
		}
		else if (from.x != 0.0f || from.z != 0.0f) {

			n = { from.z, 0.0f, -from.x };
		}
	}


	Matrix4x4 result = MakeRotateAxisAngle(n, sin, cos);


	return result;
}




/// -------------------------------------------------------------------------
/// クォータニオン
/// -------------------------------------------------------------------------
// 内積
float Dot(const Quaternion& q1, const Quaternion& q2) {
	return (q1.x * q2.x) + (q1.y * q2.y) + (q1.z * q2.z) + (q1.w * q2.w);
}

// 長さ
float Length(const Quaternion p) {
	return  std::sqrt(Dot(p, p));
}

// 共役Quaternionを返す
Quaternion Conjugate(const Quaternion& q) {
	return { q.w , -q.x, -q.y, -q.z };
}

// Quaternionのnormを返す
float Norm(const Quaternion& q) {
	return std::sqrt(float(pow(q.w, 2) + pow(q.x, 2) + pow(q.y, 2) + (q.z, 2)));
}

// 正規化したQuaternionを返す
Quaternion Normalize(const Quaternion& q) {
	float length = Length(q);
	return q / length;
}

// 逆Quatenionを返す
Quaternion Inverse(const Quaternion& q) {
	Quaternion result = Conjugate(q);
	float norm = float(pow(Norm(q), 2));
	return result / norm;
}

// 球面線形補間
Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t) {
	Quaternion q0 = q1;
	float dot = Dot(q1, q2);
	if (dot < 0.0f) {
		q0 = -q0;
		dot = -dot;
	}
	constexpr float EPSILON = 0.0001f;
	if (dot >= 1.0f - EPSILON) {
		return (1.0f - t) * q0 + t * q1;
	}
	float theta = std::acos(dot);
	float sinTheta = 1.0f / std::sin(theta);
	float scale1 = std::sin((1.0f - t) * theta) * sinTheta;
	float scale2 = std::sin(t * theta) * sinTheta;
	return (q0 * scale1) + (q2 * scale2);
}

// 任意軸回転を表すQuaternionの生成
Quaternion	MakeRotateAxisAngleQuatenion(const Vector3& axis, float angle) {
	float halfAngle = angle * 0.5f;
	float sinHalfAngle = sinf(halfAngle);
	float cosHalfAngle = cosf(halfAngle);
	Quaternion hr = {
		axis.x * sinHalfAngle,
		axis.y * sinHalfAngle,
		axis.z * sinHalfAngle,
		cosHalfAngle };

	return hr;
}

// ベクトルをQuaternionで回転させた結果のベクトルを求める
Vector3 RotateVector(const Vector3& v, const Quaternion& q) {
	Quaternion vecQ = { 0.0f, v.x, v.y, v.z };
	Quaternion conQ = Conjugate(q);
	Quaternion rotV = q * (vecQ * conQ);
	return { rotV.x, rotV.y, rotV.z };
}

// Quaternionから回転行列を求める
Matrix4x4 MakeRotateMatrix(const Quaternion& q) {
	Quaternion powQ = { float(pow(q.w, 2)), float(pow(q.x, 2)), float(pow(q.y, 2)), float(pow(q.z, 2)) };
	Matrix4x4 hr = Matrix4x4::identity;
	hr.m[0][0] = powQ.w + powQ.x - powQ.y - powQ.z;
	hr.m[0][1] = 2 * ((q.x * q.y) + (q.w * q.z));
	hr.m[0][2] = 2 * ((q.x * q.z) - (q.w * q.y));

	hr.m[1][0] = 2 * ((q.x * q.y) - (q.w * q.z));
	hr.m[1][1] = powQ.w - powQ.x + powQ.y - powQ.z;
	hr.m[1][2] = 2 * ((q.y * q.z) + (q.w * q.x));

	hr.m[2][0] = 2 * ((q.x * q.z) + (q.w * q.y));
	hr.m[2][1] = 2 * ((q.y * q.z) - (q.w * q.x));
	hr.m[2][2] = powQ.w - powQ.x - powQ.y + powQ.z;
	return hr;
}




