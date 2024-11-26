#pragma once

#include "Math/MyMath.h"


/* ObjectPoolクラス */
template <typename T>
class ObjectPool {

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="initSize"> 初期サイズ </param>
	ObjectPool(size_t initSize) {
		for (size_t i = 0; i < initSize; ++i) {
			pools.push_back(new T());
		}
	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ObjectPool() {
		for (T* obj : pools) {
			delete obj;
		}
	}

	T* Get() {
		for (T* obj : pools) {
			if(!obj->)
		}
	}


private:

	// オブジェクト配列
	std::vector<T*> pools;

};