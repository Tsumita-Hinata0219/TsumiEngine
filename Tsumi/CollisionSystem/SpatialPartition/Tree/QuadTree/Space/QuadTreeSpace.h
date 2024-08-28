#pragma once

#include "../../Project/Math/MyMath.h"


namespace QTree {

	// 分木の空間クラス
	template <class T>
	class QuadTreeSpace {

	public:

		// コンストラクタ、デストラクタ
		QuadTreeSpace();
		~QuadTreeSpace();

		// リンクを全てリセットする
		void ResetLink(std::shared_ptr<QuadTreeObject<T>>& obj) 
		{
			while (spTO) {
				auto next = spTO->GetNextObj();
				spTO->spPre.reset(); // 前のオブジェクトへのポインタをリセット
				spTO.reset();       // 現在のオブジェクトをリセット
				spTO = next;       // 次のオブジェクトへ進む
			}
		}

		// オブジェクトをプッシュ
		bool Push(std::unique_ptr<QuadTreeObject<T>>& obj);

		// 削除されるオブジェクトをチェック
		bool OnRemove(QuadTreeObject<T>* obj);

		// ポインタのゲッター
		inline std::unique_ptr<QuadTreeObject<T>>& GetFirstObj();


	protected:

		// 最新登録オブジェクトへのポインタ
		std::shared_ptr<QuadTreeObject> ptrLatest;
	};





#include "../Object/QuadTreeObject.h"


	// コンストラクタ
	template<class T>
	inline QuadTreeSpace<T>::QuadTreeSpace() {}


	// デストラクタ
	template<class T>
	inline QuadTreeSpace<T>::~QuadTreeSpace()
	{
		if (ptrLatest) { ResetLink(ptrLatest); }
	}


	// リンクを全てリセットする
	/*template<class T>
	inline void QuadTreeSpace<T>::ResetLink(std::shared_ptr<QuadTreeObject<T>>& obj)
	{
		while (obj) {


		}
	}*/


	// オブジェクトをプッシュ
	template<class T>
	inline bool QuadTreeSpace<T>::Push(std::unique_ptr<QuadTreeObject<T>>& obj)
	{
		return false;
	}


	// 削除されるオブジェクトをチェック
	template<class T>
	inline bool QuadTreeSpace<T>::OnRemove(QuadTreeObject<T>* obj)
	{
		return false;
	}


	// ポインタのゲッター
	template<class T>
	inline std::unique_ptr<QuadTreeObject<T>>& QuadTreeSpace<T>::GetFirstObj()
	{
		// TODO: return ステートメントをここに挿入します
	}
}

