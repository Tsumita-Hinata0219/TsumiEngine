#pragma once

#include "../../Project/Math/MyMath.h"


namespace QTree {
//
//	// 前方宣言
//	template <class T>
//	class QuadTreeObject;
//
//	// 分木の空間クラス
//	template <class T>
//	class QuadTreeSpace {
//
//	public:
//
//		// コンストラクタ
//		QuadTreeSpace();
//
//		// デストラクタ
//		~QuadTreeSpace();
//
//		// リンクを全てリセットする
//		void ResetLink(std::shared_ptr<QuadTreeObject<T>>& obj);
//
//		// オブジェクトをプッシュする
//		bool Push(std::shared_ptr<QuadTreeObject<T>>& obj);
//
//		// 削除されるオブジェクトをチェック
//		bool OnRemove(std::shared_ptr<QuadTreeObject<T>>* removeObj);
//
//		// 最初のオブジェクトの取得
//		inline std::shared_ptr<QuadTreeObject<T>>& GetFirstObj();
//
//
//	protected:
//
//		// 最新登録オブジェクトへのポインタ
//		std::shared_ptr<QuadTreeObject<T>> smartPtrLatest;
//
//	};
//
//
//
//
//
//#include "../Object/QuadTreeObject.h"
//
//
//	// コンストラクタ
//	template<class T>
//	inline QuadTreeSpace<T>::QuadTreeSpace() {}
//
//
//	// デストラクタ
//	template<class T>
//	inline QuadTreeSpace<T>::~QuadTreeSpace()
//	{
//		if (smartPtrLatest) ResetLink(smartPtrLatest);
//	}
//
//
//	// リンクを全てリセットする
//	template<class T>
//	inline void QuadTreeSpace<T>::ResetLink(std::shared_ptr<QuadTreeObject<T>>& obj)
//	{
//		if (obj->sp_Next) { ResetLink(obj->sp_Next); }
//		obj.reset();
//	}
//
//
//	// オブジェクトをプッシュする
//	template<class T>
//	inline bool QuadTreeSpace<T>::Push(std::shared_ptr<QuadTreeObject<T>>& obj)
//	{
//		return false;
//	}
//
//
//	// 削除されるオブジェクトをチェック
//	template<class T>
//	inline bool QuadTreeSpace<T>::OnRemove(std::shared_ptr<QuadTreeObject<T>>* removeObj)
//	{
//		if (smartPtrLatest.get() == removeObj) {
//			// 次のオブジェクトにすげ替え
//			if (smartPtrLatest) {
//				smartPtrLatest = smartPtrLatest->GetNextObj();
//			}
//		}
//		return true;
//	}
//
//
//	// 最初のオブジェクトの取得
//	template<class T>
//	inline std::shared_ptr<QuadTreeObject<T>>& QuadTreeSpace<T>::GetFirstObj()
//	{
//		return smartPtrLatest;
//	}
}