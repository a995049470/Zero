#pragma once
#include <cassert>
template<typename T>
class Singleton
{
	static T* m_Singleton;
public:
	Singleton()
	{
		/*assert(!m_Singleton);
		int offset = (int)(T*)1 - (int)(Singleton<T>*)(T*)1;
		m_Singleton = (T*)((int)this + offset);*/
	}

	~Singleton()
	{
		m_Singleton = 0;
	}

	static T* GetSingletionPtr()
	{
		if (!m_Singleton)
		{
			m_Singleton = new T();
		}
		return m_Singleton;
	}
	static T& GetSinleton()
	{
		if (!m_Singleton)
		{
			m_Singleton = new T();
		}
		return *m_Singleton;
	}

	static void Close()
	{
		delete m_Singleton;
		m_Singleton = 0;
	}
};

template<typename T> T* Singleton<T>::m_Singleton = 0;