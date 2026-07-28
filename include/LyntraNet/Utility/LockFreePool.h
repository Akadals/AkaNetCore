#ifndef __INCL_LYNTRA_LOCK_FREE_POOL_H__
#define __INCL_LYNTRA_LOCK_FREE_POOL_H__

#include "ConcurrentQueue.h"

namespace LyntraNet::Utility
{
	template<typename T>
	class LockFreePool
	{
	private:
	public:
		LockFreePool(size_t _size);
		T* Acquire();
		bool Release();
	};
}
#endif