#ifndef __INCL_LYNTRA_CONCURRENT_HASH_MAP_H__
#define __INCL_LYNTRA_CONCURRENT_HASH_MAP_H__

#include "ConcurrentPolicy.h"
#include <atomic>
#include <memory>

namespace LyntraNet::Utility
{
	template<typename T, ConcurrentPolicy Policy>
	class ConcurrentHashMap;


	template<typename T>
	class ConcurrentHashMap<T, SPSC>
	{

	};
	template<typename T>
	class ConcurrentHashMap<T, MPSC>
	{

	};
	template<typename T>
	class ConcurrentHashMap<T, SPMC>
	{

	};
	template<typename T>
	class ConcurrentHashMap<T, MPMC>
	{

	};
}

#include "Detail/ConcurrentHashMap/ConcurrentHashMapSPSC.inl"
#include "Detail/ConcurrentHashMap/ConcurrentHashMapMPSC.inl"
#include "Detail/ConcurrentHashMap/ConcurrentHashMapSPMC.inl"
#include "Detail/ConcurrentHashMap/ConcurrentHashMapMPMC.inl"
#endif