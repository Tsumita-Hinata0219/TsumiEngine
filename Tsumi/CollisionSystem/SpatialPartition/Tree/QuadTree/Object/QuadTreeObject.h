#pragma once

#include "../../Project/Math/MyMath.h"


namespace QTree{

	// 前方宣言
	class QuadTreeSpace;

	/* 四分木登録オブジェクト */
	template <class T>
	class QuadTreeObject {
		
	public:

		// コンストラクタ
		QuadTreeObject() 
		{
			// nullを入れておく
			p_Space = nullptr;
			p_Object = nullptr;
		}

		// デストラクタ
		~QuadTreeObject() {}


		// リストから外れる
		bool Remove() 
		{


		}


		// 空間を登録
		void RegisterSpace(QuadTreeSpace<T>* pSpace)
		{


		}


		// 次のオブジェクトを取得
		QuadTreeObject<T>& GetNextObj()
		{


		}


	public:

		// 登録空間
		QuadTreeSpace<T>* p_Space;

		// 判定対象オブジェクト
		T* p_Object;

		// 前のオブジェクト
		QuadTreeObject<T>* sp_Pre;

		// 次のオブジェクト
		QuadTreeObject<T>* sp_Next;

	};
}



