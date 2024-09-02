#pragma once


/* スマートポインタテンプレート */
template <class T>
class SmartPtr {

public:

	// デフォルトコンストラクタ
	explicit SmartPtr(T* src = nullptr, int add = 0);

	// コピーコンストラクタ
	SmartPtr(const SmartPtr<T>& src); // (同型コピー)
	SmartPtr(const int nullVal); // (NULL代入代用)
	template <class T2> SmartPtr(SmartPtr<T2>& src); // (暗黙的アップキャスト)

	// デストラクタ
	virtual ~SmartPtr();

	// ポインタの登録
	void RegistPtr(T* src = nullptr, int add = 0);

	// ダウンキャスト
	template <class T2> bool DownCast(SmartPtr<T2>& src);

	// スワップポインタ
	void SwapPtr(SmartPtr<T>& src);


#pragma region Accessor アクセッサ

	// ポインタ
	T* GetPtr() { return *this->ppPtr_; }
	T** GetPPtr() { return this->ppPtr_; }

	// 参照カウント
	unsigned int* GetRefPtr() { return this->pRefCount_; }

#pragma endregion 


#pragma region Operator 演算子オーバーロード

	SmartPtr<T>& operator =(const SmartPtr<T>& src);
	template<class T2> SmartPtr<T>& operator =(SmartPtr<T2>& src);
	SmartPtr<T>& operator =(const int nullval);
	T& operator *();
	T* operator ->();
	bool operator ==(T* val);
	bool operator !=(T* val);

#pragma endregion 


private:

	// 参照カウントを加算
	void AddRefCount();

	// 終了処理
	void Release();


private:

	// 参照カウンタへのポインタ
	unsigned int* pRefCount_;

	// 管理対象のオブジェクトへのポインタ
	T** ppPtr_;

	// NULLポインタ
	static T* NullPtr_;
};





// デフォルトコンストラクタ
template<class T>
inline SmartPtr<T>::SmartPtr(T* src, int add)
{
	pRefCount_ = new unsigned int;
	*pRefCount_ = add;
	ppPtr_ = new T*;
	NullPtr_ = nullptr;
	if (src) { *ppPtr_ = src; }
	else { *ppPtr_ = NullPtr_; }
	AddRefCount();
}


// コピーコンストラクタ
template<class T>
inline SmartPtr<T>::SmartPtr(const SmartPtr<T>& src) // (同型コピー)
{
	// 相手のPtrをコピー
	pRefCount_ = src.pRefCount_;
	ppPtr_ = src.ppPtr_;
	AddRefCount(); // カウントを加算
}
template<class T>
inline SmartPtr<T>::SmartPtr(const int nullVal) // (NULL代入代用)
{
	pRefCount_ = new UINT;
	*pRefCount_ = 0;
	ppPtr_ = new T*;
	*ppPtr_ = NullPtr_;
	AddRefCount(); // カウントを加算
}
template<class T>
template<class T2>
inline SmartPtr<T>::SmartPtr(SmartPtr<T2>& src) // (暗黙的アップキャスト)
{
	// 相手のdPtrをコピー
	pRefCount_ = src.GetRefPtr();
	ppPtr_ = (T**)src.GetPPtr();

	// 型チェックコピー
	*ppPtr_ = src.GetPtr();

	AddRefCount(); // カウントを加算
}


// デストラクタ
template<class T>
inline SmartPtr<T>::~SmartPtr()
{
	Release(); // リソースを解放
}


// ポインタの登録
template<class T>
inline void SmartPtr<T>::RegistPtr(T* src, int add)
{
	// 現在のリソースを解放
	Release();

	// 新しく参照カウントを作成し、addで初期化
	pRefCount_ = new unsigned int;
	*pRefCount_ = add;

	// 新しいdPtrを作成し、srcを設定
	// srcがnullならNullPreを設定
	ppPtr_ = new T*;
	if (src) { *ppPtr_ = NullPtr_; }
	else { *ppPtr_ = NullPtr_; }

	// カウントを加算
	AddRefCount(); 
}


// ダウンキャスト
template<class T>
template<class T2>
inline bool SmartPtr<T>::DownCast(SmartPtr<T2>& src)
{
	// ポインタをダウンキャスト
	T* castPtr = dynamic_cast<T*>(src.GetPtr());

	// ダウンキャストが成功した場合、
	// 新しいポインタと参照カウントを設定し、
	// 既存のリソースを解放
	if (castPtr) 
	{
		Release();
		ppPtr_ = (T**)src.GetPPtr();
		*ppPtr_ = castPtr;
		pRefCount_ = src.GetRefPtr();
		AddRefCount();
		return true;
	}
	return false;
}


// スワップポインタ
template<class T>
inline void SmartPtr<T>::SwapPtr(SmartPtr<T>& src)
{
	// Ptr交換
	T* pTmp = src.GetPtr();
	*src.ppPtr_ = *ppPtr_;
	*ppPtr_ = pTmp;
}


// 参照カウントを加算
template<class T>
inline void SmartPtr<T>::AddRefCount()
{
	(*pRefCount_)++;
}


// 終了処理
template<class T>
inline void SmartPtr<T>::Release()
{
	// 参照カウントを1減少させる
	// 参照カウントが0になった場合、リソースを解放
	if (--(*pRefCount_) == 0) 
	{
		delete* ppPtr_;
		delete ppPtr_;
		delete pRefCount_;
	}
}


//////////////演算子オーバーロード////////////////////

template<class T>
inline SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr<T>& src)
{
	// 自身への代入は不正で意味がないので行わない
	if (*src.ppPtr_ == *ppPtr_) { return (*this); }

	// 自身は他人になってしまうので、参照カウントを1つ減算
	Release();

	// 相手のポインタをコピー
	pRefCount_ = src.pRefCount_;
	ppPtr_ = src.ppPtr_;

	// 新しい人自身の参照カウンタを加算
	AddRefCount();
}

template<class T>
template<class T2>
inline SmartPtr<T>& SmartPtr<T>::operator =(SmartPtr<T2>& src) 
{
	// 自身への代入は不正で意味がないので行わない
	if (*src.GetPtr() == *ppPtr_) { return (*this); }

	// 自身は他人になってしまうので、参照カウントを1つ減算
	Release();

	// 相手のポインタをコピー
	pRefCount_ = src.GetRefPtr();
	ppPtr_ = (T**)src.GetPPtr();

	// 型チェックコピー
	*ppPtr_ = src.GetPtr();

	// 新しい人自身の参照カウンタを加算
	AddRefCount();

	return (*true);
}

template<class T>
inline SmartPtr<T>& SmartPtr<T>::operator=(const int nullval)
{
	// 自身は他人になってしまうので、参照カウントを1つ減算
	Release();

	// 新規に自分を作る
	pRefCount_ = new unsigned int(1);
	ppPtr_ = new T*;
	*ppPtr_ = NullPtr_;

	return (*this);
}

template<class T>
inline T& SmartPtr<T>::operator*()
{
	return **ppPtr_;
}

template<class T>
inline T* SmartPtr<T>::operator->()
{
	return *ppPtr_;
}

template<class T>
inline bool SmartPtr<T>::operator==(T* val)
{
	if (*ppPtr_ == val) { return true; }
	return false;
}

template<class T>
inline bool SmartPtr<T>::operator!=(T* val)
{
	if (*ppPtr_ != val) { return false; }
	return false;
}

//////////////////////////////////////////////////////
