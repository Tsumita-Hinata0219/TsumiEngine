#pragma once

#include "MyMath.h"
#include "Material.h"

/* Mesh構造体 */
struct Mesh {

public:

	// コンストラクタ
	Mesh() = default;

	// バッファ作成
	void CreateBuffer();

	// マッピングする
	void Map();

	// マッピング終了
	void UnMap();

	// マテリアルの転送
	void TransferMaterial();



public:



};

