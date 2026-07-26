#include "RingBuffer.h"

namespace LyntraNet::Utility
{
	template<typename T>
	class alignas(64) RingBuffer<T, SPMC>
	{

	};
}