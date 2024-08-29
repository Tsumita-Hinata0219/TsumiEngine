#pragma once

#include "../Project/Math/MyMath.h"


// 四分木
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
		std::shared_ptr<QuadTreeObject<T>> sp_Pre;

		// 次のオブジェクト
		std::shared_ptr<QuadTreeObject<T>> sp_Next;


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





	// 分木の空間クラス
	template <class T>
	class QuadTreeSpace {

	protected:

		// 最新登録オブジェクトへのポインタ
		std::shared_ptr<QuadTreeObject<T>> smartPtrLatest;


	public:

		// コンストラクタ
		QuadTreeSpace() {}


		// デストラクタ
		~QuadTreeSpace()
		{
			if (smartPtrLatest) ResetLink(smartPtrLatest);
		}


		// リンクを全てリセットする
		void ResetLink(std::shared_ptr<QuadTreeObject<T>>& obj)
		{
			if (obj->sp_Next) { ResetLink(obj->sp_Next); }
			obj.reset();
		}


		// オブジェクトをプッシュする
		bool Push(std::shared_ptr<QuadTreeObject<T>>& obj)
		{
			// 無効オブジェクトは登録しない
			if (!obj) { return false; }
			// ２重登録チェック
			if (obj->p_Space == this) { return false; }

			if (!smartPtrLatest)
			{
				// 空間に新規登録
				smartPtrLatest = obj;
			}
			else 
			{
				// 最新TreeObjectオブジェクトを更新
				obj->sp_Next = smartPtrLatest;
				smartPtrLatest->sp_Pre = obj;
				smartPtrLatest = obj;
			}

			// 空間を登録
			obj->RegisterSpace(this);

			return true;
		}


		// 削除されるオブジェクトをチェック
		bool OnRemove(std::shared_ptr<QuadTreeObject<T>>* removeObj)
		{
			if (smartPtrLatest.get() == removeObj) 
			{
				// 次のオブジェクトにすげ替え
				if (smartPtrLatest) 
				{
					smartPtrLatest = smartPtrLatest->GetNextObj();
				}
			}
			return true;
		}


		// 最初のオブジェクトの取得
		inline std::shared_ptr<QuadTreeObject<T>>& GetFirstObj()
		{
			return smartPtrLatest;
		}

	};





}

