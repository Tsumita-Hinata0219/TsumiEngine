#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <dxcapi.h>
#include <string>
#include <wrl.h>
#include <format>

#include "MyMath.h"
#include "EnumUtilities.h"


struct Shaders {
	IDxcUtils* Utils;
	IDxcCompiler3* Compiler;
	IDxcIncludeHandler* includeHandler;
};


struct ShadersMode {
	IDxcBlob* VertexBlob;
	IDxcBlob* PixelBlob;
};


struct ShadersType {
	ShadersMode Noraml;
	ShadersMode Sprite;
	ShadersMode Light;
	ShadersMode Lambert;
	ShadersMode Phong;
	ShadersMode PhongNormalMap;
	ShadersMode Particle;
	ShadersMode Line;
	ShadersMode Object3d;
	ShadersMode PostEffect;
};

enum class ModelShaders {
	Normal,
	Sprite,
	Light,
	Lambert,
	Phong,
	PhongNormalMap,
	Particle,
	Line,
	Object3D,
	Count,
};
enum class PostEffectShaders {
	BoxFilter,
	Dissolve,
	GaussianFilter,
	GrayScale,
	OutLine,
	RadialBlur,
	Random,
	SepiaTone,
	Vignetting,
	Count,
};


class ShaderManager {

private: // シングルトンデザインパターン

	// コンストラクタ、デストラクタ
	ShaderManager() = default;
	~ShaderManager() = default;
	ShaderManager(const ShaderManager&) = delete;
	const ShaderManager& operator=(const ShaderManager&) = delete;


public: // メンバ関数

	/// <summary>
	/// ShaderManagerのインスタンス取得
	/// </summary>
	static ShaderManager* GetInstance() {
		static ShaderManager instance;
		return &instance;
	}

	/// <summary>
	/// 初期化処理
	/// </summary>
	static void Initialize();

#pragma region Get 取得

	/// <summary>
	/// 
	/// </summary>
	ShadersType GetShaderType() { return ShaderManager::GetInstance()->shaders_; }

#pragma endregion


private: // メンバ関数

	/// <summary>
	/// CompileShader関数
	/// </summary>
	IDxcBlob* CompileShader(
		const std::wstring& filePath,
		const wchar_t* profile);

	/// <summary>
	/// DXCの初期化
	/// </summary>
	void InitializeDXC();

	/// <summary>
	/// includeに対応するための設定
	/// </summary>
	void SettingIncludeHandler();

	/// <summary>
	/// シェーダーをコンパイルする
	/// </summary>
	void ModelShadersCompiles();
	void PostEffectShadersCompiles();

	/// <summary>
	/// シェーダーをセットする
	/// </summary>
	void SetShader(const std::wstring& vertexPath, const std::wstring& pixelPath, ShadersMode& shader);

#pragma region ModelShaders

	void NormalShader();
	void SpriteShader();
	void LightShader();
	void LambertShader();
	void PhongShader();
	void PhongNormalMapShader();
	void ParticleShader();
	void LineShader();
	void Object3DShader();

#pragma endregion

#pragma region PostEffectShaders

	void PostEffectShader();
	void BoxFilterShader();
	void DissolveShader();
	void GaussianFilterShader();
	void GrayScaleShader();
	void OutLineShader();
	void RadialBlurShader();
	void RandomShader();
	void SepiaToneShader();
	void VignettingShader();

#pragma endregion


private: // メンバ変数

	Shaders dxc_{};
	ShadersType shaders_{};
	ShadersMode shaderArray_{};

	std::vector<ShadersMode> shadersVector_{};
	std::vector<ShadersMode> modelShaders_{};
	std::vector<ShadersMode> postEffectShaders_{};
};