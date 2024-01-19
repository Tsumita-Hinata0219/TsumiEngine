#pragma once
#include "DirectXCommon.h"
#include "Struct.h"
#include "CreateResource.h"


//
//struct TransformationMatrix {
//	Matrix4x4 WVP;
//	Matrix4x4 World;
//};

struct TransformationViewMatrix {
	Matrix4x4 view;
	Matrix4x4 viewProjection;
	Matrix4x4 orthoGraphic;
	Vector3 position;
};

struct ParticleTransformationMatrix {
	Matrix4x4 WVP;
	Matrix4x4 World;
	Vector4 Color;
	Matrix4x4 uvTansform;
};


struct ResourcePeroperty {
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW VertexBufferView;
	// 頂点バッファビュー
	D3D12_INDEX_BUFFER_VIEW IndexBufferView;
	// 頂点リソース用のヒープ設定
	ComPtr<ID3D12Resource> Vertex;
	// 
	ComPtr<ID3D12Resource> Index;
	// 
	ComPtr<ID3D12Resource> TransformationMatrix;
	// 
	ComPtr<ID3D12Resource> Material;
	// 
	ComPtr<ID3D12Resource> Lighting;
	// 
	ComPtr<ID3D12Resource> instancing;
};


class CreateResource {

public:

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	static CreateResource* GetInstance();

	/// <summary>
	/// 頂点バッファリソースを作成する
	/// </summary>
	static ComPtr<ID3D12Resource> CreateBufferResource(size_t sizeInBytes);

	static void CreateBufferResource(size_t sizeInBytes, ComPtr<ID3D12Resource>& resource);

	/// <summary>
	/// 頂点バッファビューを作成する
	/// </summary>
	static D3D12_VERTEX_BUFFER_VIEW CreateVertexBufferView(size_t sizeInbyte, ID3D12Resource* resource, int size);
	static D3D12_INDEX_BUFFER_VIEW CreateIndexBufferview(size_t sizeInbyte, ID3D12Resource* resource);

private:

};

