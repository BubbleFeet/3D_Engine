#ifndef INCLUDED_CORE_DELETEUTIL_H
#define INCLUDED_CORE_DELETEUTIL_H

// Description: Helpers for deallocation.

#include "Common.h"

template<typename T>
inline void SafeDelete(T*& ptr)
{
	delete ptr;
	ptr = nullptr;
}

template<typename T>
inline void SafeDeleteArray(T*& ptr)
{
	delete[] ptr;
	ptr = nullptr;
}

template<typename T>
inline void SafeDeleteVector(std::vector<T*> vec)
{
	for (auto element : vec)
	{
		SafeDelete(element);
	}

	vec.clear();
}

template <typename T>
inline void SafeRelease(T*& ptr)
{
	if (ptr != nullptr)
	{
		ptr->Release();
		ptr = nullptr;
	}
}

#endif // #ifndef INCLUDED_CORE_DELETEUTIL_H

