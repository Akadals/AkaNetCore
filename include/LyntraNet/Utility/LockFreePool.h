#ifndef __INCL_LYNTRA_LOCK_FREE_POOL_H__
#define __INCL_LYNTRA_LOCK_FREE_POOL_H__

#include "ConcurrentStack.h"

namespace LyntraNet::Utility
{
	template<typename T>
	class LockFreePool
	{
	private:
		ConcurrentStack<T, MPMC> m_stack;
	public:
		LockFreePool(size_t _size) : m_stack(_size){}
		T* Acquire();
		bool Release();
	};
}
#endif