#pragma once

#include <memory>

#include "../../Project/Math/MyMath.h"

#include "../Space/QuadTreeSpace.h"


namespace QTree {

	// 前方宣言
	template <class T>
	class QuadTreeSpace;

	/* 四分木登録オブジェクト */
	template <class T>
	class QuadTreeObject {

	public:

		// 登録空間
		QuadTreeSpace<T>* p_Space;
		// 判定対象オブジェクト
		T* p_Object;
		// 前のオブジェクト
		std::weak_ptr<QuadTreeObject<T>> sp_Pre;
		// 次のオブジェクト
		std::shared_ptr<QuadTreeObject<T>> sp_Next;

		QuadTreeObject<T>* ok;

	public:

		// コンストラクタ
		QuadTreeObject()
		{
			// nullを入れておく
			p_Space = nullptr;
			p_Object = nullptr;
		}

		// デストラクタ
		~QuadTreeObject() {};

		// リストから外れる
		bool Remove()
		{
			// 既に逸脱しているときは処理終了
			if (!p_Space) { return false; }

			// 自分を登録している空間に自身を通知
			if (!p_Space->OnRemove(this)) { return false; }

			// 逸脱処理
			// 前後のオブジェクトを結びつける
			if (sp_Pre != nullptr) 
			{

			}
		}

		// 空間を登録
		void RegisterSpace(QuadTreeSpace<T>* pSpace)
		{
			p_Space = pSpace;
		}

		// 次のオブジェクトを取得
		std::shared_ptr<QuadTreeObject<T>> GetNextObj() const
		{
			return sp_Next;
		}
	};
}
