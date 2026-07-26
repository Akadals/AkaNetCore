#pragma once
#include <atomic>
#include <vector>
#include <memory>

namespace LyntraNet::Utility
{
	struct SPSC {};
	struct MPSC {};
	struct SPMC {};
	struct MPMC {};

	template<typename T, typename Policy>
	class alignas(64) RingBuffer;
}