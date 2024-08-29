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

		// コンストラクタ
		QuadTreeObject();

		// デストラクタ
		~QuadTreeObject();

		// リストから外れる
		bool Remove();

		// 空間を登録
		void RegisterSpace(QuadTreeSpace<T>* pSpace);

		// 次のオブジェクトを取得
		std::shared_ptr<QuadTreeObject<T>> GetNextObj() const;


	public:

		// 登録空間
		QuadTreeSpace<T>* p_Space;

		// 判定対象オブジェクト
		T* p_Object;

		// 前のオブジェクト
		std::shared_ptr<QuadTreeObject<T>> sp_Pre;

		// 次のオブジェクト
		std::shared_ptr<QuadTreeObject<T>> sp_Next;

	};





	// コンストラクタ
	template<class T>
	inline QuadTreeObject<T>::QuadTreeObject()
	{
		// nullを入れておく
		p_Space = nullptr;
		p_Object = nullptr;
	}


	// デストラクタ
	template<class T>
	inline QuadTreeObject<T>::~QuadTreeObject()
	{
	}


	// リストから外れる
	template<class T>
	inline bool QuadTreeObject<T>::Remove()
	{
		// 既に逸脱しているときは処理終了
		if (!p_Space) { return false; }

		// 自分を登録している空間に自身を通知
		if (!p_Space->OnRemove(this)) { return false; }

		// 逸脱処理
		// 前後のオブジェクトを結びつける
		if (sp_Pre)
		{
			sp_Pre->sp_Next = sp_Next;
			sp_Pre.RegistPtr(nullptr);
		}
		if (sp_Next)
		{
			sp_Next->sp_Pre = sp_Pre;
			sp_Next.reset();
		}

		p_Space = nullptr;
		return true;
	}


	// 空間を登録
	template<class T>
	inline void QuadTreeObject<T>::RegisterSpace(QuadTreeSpace<T>* pSpace)
	{
		p_Space = pSpace;
	}


	// 次のオブジェクトを取得
	template<class T>
	inline std::shared_ptr<QuadTreeObject<T>> QuadTreeObject<T>::GetNextObj() const
	{
		return sp_Next;
	}
}

