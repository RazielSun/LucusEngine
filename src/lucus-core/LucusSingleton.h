//
//  LucusGame
//
//  Created by Alexander Kardakov
//

#ifndef _LUCUS_ENGINE_SINGLETON_H
#define _LUCUS_ENGINE_SINGLETON_H

namespace LucusEngine
{
	template<class T>
	class Singleton
	{
	protected:
		static T* mInstance;

	public:
		Singleton()
		{
			// assert(mInstance == nullptr);
			mInstance = static_cast< T* >( this );
		}
		Singleton( const Singleton<T> &) = delete;
		Singleton& operator=( const Singleton<T> &) = delete;

		~Singleton()
		{
			// assert(mInstance)
			mInstance = nullptr;
		}
	
		static T& Get() { return *mInstance; }

		static T* GetPtr() { return mInstance; }
	};
}

#endif //_LUCUS_ENGINE_SINGLETON
