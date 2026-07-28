#ifndef __INCL_LYNTRA_CONCURRENT_STACK_H__
#define __INCL_LYNTRA_CONCURRENT_STACK_H__

#include "ConcurrentPolicy.h"
#include <atomic>
#include <memory>

namespace LyntraNet::Utility
{
	template<typename T, ConcurrentPolicy Policy>
	class ConcurrentStack;

	template<typename T>
	class ConcurrentStack<T, SPSC>
	{

	};
	template<typename T>
	class ConcurrentStack<T, MPSC>
	{

	};
	template<typename T>
	class ConcurrentStack<T, SPMC>
	{

	};
	template<typename T>
	class ConcurrentStack<T, MPMC>
	{

	};
}

#include "Detail/ConcurrentStack/ConcurrentStackSPSC.inl"
#include "Detail/ConcurrentStack/ConcurrentStackMPSC.inl"
#include "Detail/ConcurrentStack/ConcurrentStackSPMC.inl"
#include "Detail/ConcurrentStack/ConcurrentStackMPMC.inl"
#endif
