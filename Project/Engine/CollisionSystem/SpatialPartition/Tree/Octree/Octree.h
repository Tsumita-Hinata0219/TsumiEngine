#pragma once

#include "Math/MyMath.h"

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
		OctreeSpace<T>* p_Space;

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
	template <class T>
	class Liner8Tree {

	protected:

		// 空間の深さ
		unsigned int m_dimension;

		// 線形空間ポインタ配列
		OctreeSpace<T>** m_cellArray;

		// 8のべき乗数配列
		unsigned int m_powerOfEight[OCTREE_MAX_LEVEL_DEPTH + 1];

		// 領域の幅
		Vector3 m_regionSize{};

		// 領域の最小値
		Vector3 m_regionMin{};

		// 領域の最大値
		Vector3 m_regionMax{};

		// 最小領域の辺の長さ
		Vector3 m_unitSize{};

		// 空間の数
		DWORD m_totalCells;

		//  最下位レベル
		unsigned int m_maxLevel;


	public:

		// コンストラクタ
		Liner8Tree() 
		{
			m_dimension = 0;
			m_cellArray = nullptr;
			m_regionSize = Vector3::one;
			m_regionMin = Vector3::zero;
			m_regionMax = Vector3::one;
			m_unitSize = Vector3::one;
			m_totalCells = 0;
			m_maxLevel = 0;
		}


		// デストラクタ
		virtual ~Liner8Tree()
		{
			for (DWORD i = 0; i < m_totalCells; ++i) 
			{
				if (m_cellArray[i] != nullptr) { delete m_cellArray[i]; }
			}
			delete[] m_cellArray;
		}


		// 初期化処理
		bool Init(const unsigned int level, const Vector3& min, const Vector3& max)
		{
			// 線形八分木配列を構築する
			if (level >= OCTREE_MAX_LEVEL_DEPTH) { return false; }

			// 各レベルでの空間数を算出
			m_powerOfEight[0] = 1;
			for (int i = 1; i < OCTREE_MAX_LEVEL_DEPTH; i++)
			{
				m_powerOfEight[i] = m_powerOfEight[i - 1] * 8;
			}

			// Level1(0基点)の配列作成
			m_totalCells = (m_powerOfEight[level + 1] - 1) / 7;
			m_cellArray = new OctreeSpace<T>*[m_totalCells];
			ZeroMemory(m_cellArray, sizeof(OctreeSpace<T>*) * m_totalCells);

			// 領域を登録
			m_regionMin = min;
			m_regionMax = max;
			m_regionSize = m_regionMax - m_regionMin;
			m_unitSize = m_regionSize / static_cast<float>(1 << level);
			m_maxLevel = level;

			return true;
		}


		// オブジェクトを登録する
		bool RegisterObject(const Vector3& min, const Vector3& max, OctreeObject<T>* obj)
		{
			DWORD cellIndex = GetMortonNumber(min, max);
			if (cellIndex < m_totalCells) 
			{
				if (!m_cellArray[cellIndex]){ CreateNewCell(cellIndex); }
				return m_cellArray[cellIndex]->Push(obj);
			}
			return false;
		}

		// 衝突判定リストを作成する
		bool GetAllCollisionList(std::vector<T*>& collisionList)
		{
			collisionList.clear();

			if (m_cellArray[0] == nullptr) { return 0; }

			std::list<T*> collisionStack;
			GetCollisionList(0, collisionList, collisionStack);

			return static_cast<DWORD>(collisionList.size());
		}

		// 特定の位置から衝突の可能性があるリストを作成する
		DWORD GetTargetCollisionList(std::vector<T*>& collisionList, const Vector3& min, const Vector3& max)
		{
			collisionList.clear();

			DWORD cellIndex = GetMortonNumber(min, max);

			if (m_cellArray[cellIndex] == nullptr)
			{ 
				return 0;
			}

			GetCollisionList2(cellIndex, collisionList);

			if (cellIndex == 0)
			{ 
				return static_cast<DWORD>(collisionList.size()); 
			}

			cellIndex = (cellIndex - 1) >> 3;
			if (m_cellArray[cellIndex] == nullptr)
			{ 
				return static_cast<DWORD>(collisionList.size()); 
			}

			GetBackCollisionList(cellIndex, collisionList);

			return static_cast<DWORD>(collisionList.size());
		}


	protected:

		bool GetCollisionList(const DWORD& cellIndex, std::vector<T*>& collisionList, std::list<T*>& collisionStack)
		{
			//std::list<T*>::iterator it;
			typename std::list<T*>::iterator it;

			// 空間内のオブジェクト同士の衝突リスト作成
			OctreeObject<T>* obj1 = m_cellArray[cellIndex]->GetFirstObj();
			while (obj1 != nullptr) 
			{
				OctreeObject<T>* obj2 = obj1->spNext;
				while (obj2 != nullptr) 
				{
					collisionList.push_back(obj1->pObject);
					collisionList.push_back(obj2->pObject);
					obj2 = obj2->spNext;
				}

				// 衝突スタックとの衝突リスト作成
				for (it = collisionStack.begin(); it != collisionStack.end(); ++it) 
				{
					collisionList.push_back(obj1->pObject);
					collisionList.push_back(*it);
				}
				obj1 = obj1->spNext;
			}

			bool hasChildCells = false;
			DWORD numObjectsInStack = 0;

			for (DWORD i = 0; i < 8; i++)
			{
				DWORD nextCellIndex = cellIndex * 8 + 1 + i;
				if (nextCellIndex < m_totalCells && m_cellArray[nextCellIndex])
				{
					if (!hasChildCells)
					{
						obj1 = m_cellArray[cellIndex]->GetFirstObj();
						while (obj1)
						{
							collisionStack.push_back(obj1->pObject);
							numObjectsInStack++;
							obj1 = obj1->spNext;
						}
					}
					hasChildCells = true;
					GetCollisionList(nextCellIndex, collisionList, collisionStack); // 子空間へ
				}
			}

			// スタックからオブジェクトを外す
			if (hasChildCells) 
			{
				for (DWORD i = 0; i < numObjectsInStack; i++)
				{
					collisionStack.pop_back();
				}
			}

			return true;
		}

		bool GetCollisionList2(DWORD cellIndex, std::vector<T*>& collisionList)
		{
			// 空間内のオブジェクト同士の衝突リスト作成
			OctreeObject<T>* obj = m_cellArray[cellIndex]->GetFirstObj();
			while (obj != nullptr) 
			{
				collisionList.push_back(obj->pObject);
				obj = obj->spNext;
			}

			for (DWORD i = 0; i < 8; i++) 
			{
				DWORD nextCellIndex = cellIndex * 8 + 1 + i;
				if (nextCellIndex < m_totalCells && m_cellArray[nextCellIndex]) 
				{
					GetCollisionList2(nextCellIndex, collisionList); // 子空間へ
				}
			}

			return true;
		}

		bool GetBackCollisionList(DWORD cellIndex, std::vector<T*>& collisionList)
		{
			// 空間内のオブジェクト同士の衝突リスト作成
			OctreeObject<T>* obj = m_cellArray[cellIndex]->GetFirstObj();
			while (obj != nullptr) 
			{
				collisionList.push_back(obj->pObject);
				obj = obj->spNext;
			}

			if (cellIndex > 0) 
			{
				DWORD parentCellIndex = (cellIndex - 1) >> 3;
				if (m_cellArray[parentCellIndex]) 
				{
					GetBackCollisionList(parentCellIndex, collisionList); // 親空間へ
				}
			}

			return true;
		}


		// 空間を生成
		bool CreateNewCell(DWORD cellIndex) {
			while (!m_cellArray[cellIndex]) {
				m_cellArray[cellIndex] = new OctreeSpace<T>;
				cellIndex = (cellIndex - 1) >> 3;
				if (cellIndex >= m_totalCells) break;
			}
			return true;
		}

		// 座標から空間番号を算出
		DWORD GetMortonNumber(const Vector3& min, const Vector3& max) {
			DWORD leftTop = GetPointElem(min + 100);
			DWORD rightBottom = GetPointElem(max + 100);

			DWORD diff = rightBottom ^ leftTop;
			unsigned int highestLevel = 1;

			for (unsigned int i = 0; i < m_maxLevel; i++) {
				DWORD check = (diff >> (i * 3)) & 0x7;
				if (check != 0)
					highestLevel = i + 1;
			}

			DWORD cellNumber = rightBottom >> (highestLevel * 3);
			DWORD nextCellNumber = cellNumber >> 3;

			DWORD cellIndex = (m_powerOfEight[highestLevel] - 1) / 7 + cellNumber;
			DWORD nextCellIndex = (m_powerOfEight[highestLevel - 1] - 1) / 7 + nextCellNumber;

			return (m_cellArray[cellIndex] || highestLevel == m_maxLevel) ? cellIndex : nextCellIndex;
		}

		// 座標から空間要素を取得
		DWORD GetPointElem(Vector3 point) {
			point = (point - m_regionMin) / m_unitSize;
			DWORD cellX = static_cast<DWORD>(point.x);
			DWORD cellY = static_cast<DWORD>(point.y);
			DWORD cellZ = static_cast<DWORD>(point.z);
			return _Interleave(cellX, cellY, cellZ);
		}

		// 空間座標を整数に変換
		DWORD _Interleave(DWORD cellX, DWORD cellY, DWORD cellZ) {
			DWORD result = 0;
			for (int i = 0; i < 32; ++i) {
				result |= ((cellX >> i) & 1) << (3 * i);
				result |= ((cellY >> i) & 1) << (3 * i + 1);
				result |= ((cellZ >> i) & 1) << (3 * i + 2);
			}
			return result;
		}

	};
}