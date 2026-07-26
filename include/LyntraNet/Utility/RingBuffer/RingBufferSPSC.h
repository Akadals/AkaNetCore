#include "RingBuffer.h"

namespace LyntraNet::Utility
{
	template<typename T>
	class alignas(64) RingBuffer<T, SPSC>
	{
	private:
		std::unique_ptr<T[]> m_buffer;

		size_t m_capacity;
		size_t m_mask;

		mutable alignas(64) std::atomic<size_t> m_head = 0;
		mutable alignas(64) std::atomic<size_t> m_tail = 0;
	public:
		RingBuffer(size_t _size);
		bool Push(const T* __restrict _dest, size_t _len);
		bool Pop(T* __restrict _dest, size_t _len);
		bool Peek(T* __restrict _dest, size_t _len) const;
		size_t Size() const;
		void Clear();
	};
}