#pragma once

#include "../Project/Math/MyMath.h"

#define OCTREE_MAX_LEVEL_DEPTH 7


// 八分木
namespace OTree {

	// 前方宣言
	template <class T>
	class OctreeSpace;

	/*  八分木登録オブジェクト */
	template <class T>
	class OctreeObject {

	public:

		// 登録空間
		QuadTreeSpace<T>* p_Space;

		// 判定対象オブジェクト
		T* p_Object;

		// 前のオブジェクト
		std::shared_ptr<OctreeObject<T>> sp_Pre;

		// 次のオブジェクト
		std::shared_ptr<OctreeObject<T>> sp_Next;


	public:


		// コンストラクタ
		OctreeObject()
		{
			// nullを入れておく
			p_Space = nullptr;
			p_Object = nullptr;
		}


		// デストラクタ
		~OctreeObject() {}


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
		void RegisterSpace(OctreeSpace<T>* pSpace)
		{
			p_Space = pSpace;
		}


		// 次のオブジェクトを取得
		std::shared_ptr<OctreeObject<T>> GetNextObj() const
		{
			return sp_Next;
		}
	};





	/* 八分木の空間クラス */
	template <class T>
	class OctreeSpace {

	protected:

		// 最新登録オブジェクトへのポインタ
		std::shared_ptr<OctreeObject<T>> smartPtrLatest;


	public:

		// コンストラクタ
		OctreeSpace() {}


		// デストラクタ
		~OctreeSpace()
		{
			if (smartPtrLatest) ResetLink(smartPtrLatest);
		}


		// リンクを全てリセットする
		void ResetLink(std::shared_ptr<OctreeObject<T>>& obj)
		{
			if (obj->sp_Next) { ResetLink(obj->sp_Next); }
			obj.reset();
		}


		// オブジェクトをプッシュする
		bool Push(std::shared_ptr<OctreeObject<T>>& obj)
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
		bool OnRemove(std::shared_ptr<OctreeObject<T>>* removeObj)
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
		inline std::shared_ptr<OctreeObject<T>>& GetFirstObj()
		{
			return smartPtrLatest;
		}

	};





	/* 線形八分木クラス */
	class Liner8Tree {

	protected:


	public:



	private:


	};
}