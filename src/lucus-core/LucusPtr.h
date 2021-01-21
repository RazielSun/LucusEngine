//
//  LucusPtr.h
//  LucusGame
//
//  Created by Alexander Kardakov on 08/05/2020.
//  Copyright © 2020 Alexander Kardakov. All rights reserved.
//

#ifndef _LUCUS_ENGINE_PTR_H
#define _LUCUS_ENGINE_PTR_H

namespace LucusEngine
{
	template<class T>
	class Ptr
	{
		template<class U> friend class Ptr;

	public:
		Ptr() : mPtr(nullptr) {}

		Ptr(T* ptr) : mPtr(ptr)
		{
			AddRef();
		}

		Ptr(const Ptr<T>& copy) : mPtr(copy.Get())
		{
			AddRef();
		}

		template<class U>
		Ptr(const Ptr<U>& copy) : mPtr(copy.Get())
		{
			AddRef();
		}
        
        Ptr(Ptr<T>&& rhs)
        {
            std::swap(mPtr, rhs.mPtr);
        }

		Ptr<T>& operator=(const Ptr<T>& rhs)
		{
			if (mPtr == rhs.mPtr)
				return *this;

			ReleaseRef();
			mPtr = rhs.mPtr;
			AddRef();

			return *this;
		}

		template<class U>
		Ptr<T>& operator=(const Ptr<U>& rhs)
		{
			if (mPtr == rhs.mPtr)
				return *this;

			ReleaseRef();
			mPtr = rhs.mPtr;
			AddRef();

			return *this;
		}
        
        Ptr<T>& operator=(Ptr<T>&& rhs)
        {
            std::swap(mPtr, rhs.mPtr);
            return *this;
        }
        
        template<class U>
        Ptr<T>& operator=(Ptr<U>&& rhs)
        {
            std::swap(mPtr, rhs.mPtr);
            return *this;
        }

		~Ptr()
		{
			ReleaseRef();
		}

		T* operator->() const { return mPtr; }
		T& operator*() const { return *mPtr; }
		T* Get() const { return mPtr; }
		operator bool() { return !IsNull(); }

		void Reset()
		{
			ReleaseRef();
		}

		bool IsNull() const
		{
			return mPtr == nullptr;
		}

	protected:

		void AddRef()
		{
			if (nullptr != mPtr)
			{
				mPtr->AddRef();
			}
		}

		void ReleaseRef()
		{
			if (nullptr != mPtr)
			{
				mPtr->ReleaseRef();
				mPtr = nullptr;
			}
		}

		T* mPtr;
	};
}

#endif /* _LUCUS_ENGINE_PTR_H */
