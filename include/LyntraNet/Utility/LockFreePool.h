#ifndef __INCL_LYNTRA_LOCK_FREE_POOL_H__
#define __INCL_LYNTRA_LOCK_FREE_POOL_H__

#include "ConcurrentStack.h"

namespace LyntraNet::Utility
{
	template<typename T>
	class LockFreePoolStatic
	{
	private:
		ConcurrentStack<T, MPMC> m_stack;
	public:
		LockFreePoolStatic(size_t _size) : m_stack(_size) {}
		T* Acquire();
		void Release(T* _obj);
	};
	template<typename T>
	class LockFreePoolDynamic
	{
	public:
		LockFreePoolDynamic(size_t _size);
	};
}
#endif