#include <LyntraNet/Utility/RingBuffer/RingBufferSPSC.h>

using namespace LyntraNet::Utility;

template<typename T>
RingBuffer<T, SPSC>::RingBuffer(size_t _size)
{
	size_t cap = 1;
	while (cap < _size) cap <<= 1;

	m_mask = (m_capacity = cap) - 1;
	m_buffer = std::make_unique<T[]>(m_capacity);
}

template<typename T>
bool RingBuffer<T,SPSC>::Push(const T* __restrict _dest, size_t _len)
{
	if (!_len) return true;

	size_t h = m_head.load(std::memory_order_acquire);
	size_t t = m_tail.load(std::memory_order_relaxed);

	if ((t + _len) - h > m_capacity) return false;

	size_t idx = t & m_mask;

	if (_len >= 0x40)
	{
		_mm_prefetch((char*)&m_buffer[idx], _MM_HINT_T0);
		_mm_prefetch((char*)&m_buffer[0], _MM_HINT_T0);
	}

	size_t resume = m_capacity - idx;
	size_t first = _len < resume ? _len : resume;

	if constexpr (std::is_trivially_copyable_v<T>)
	{
		memcpy(&m_buffer[idx], _dest, first * sizeof(T));
		memcpy(&m_buffer[0], _dest + first, (_len - first) * sizeof(T));
	}
	else
	{
		std::copy_n(_dest, first, &m_buffer[idx]);
		std::copy_n(_dest + first, _len - first, &m_buffer[0]);
	}

	m_tail.store(t + _len, std::memory_order_release);

	return true;
}

template<typename T>
bool RingBuffer<T, SPSC>::Pop(T* __restrict _dest, size_t _len)
{
	if (!_len) return true;

	size_t h = m_head.load(std::memory_order_relaxed);
	size_t t = m_tail.load(std::memory_order_acquire);

	if (t - h < _len) return false;

	size_t idx = h & m_mask;

	if (_len >= 0x40)
	{
		_mm_prefetch((char*)&m_buffer[idx], _MM_HINT_T0);
		_mm_prefetch((char*)&m_buffer[0], _MM_HINT_T0);
	}

	size_t resume = m_capacity - idx;
	size_t first = _len < resume ? _len : resume;

	if constexpr (std::is_trivially_copyable_v<T>)
	{
		memcpy(_dest, &m_buffer[idx], first * sizeof(T));
		memcpy(_dest + first, &m_buffer[0], (_len - first) * sizeof(T));
	}
	else
	{
		std::copy_n(&m_buffer[idx], first, _dest);
		std::copy_n(&m_buffer[0], _len - first, _dest + first);
	}

	m_head.store(t + _len, std::memory_order_release);

	return true;
}

template<typename T>
bool RingBuffer<T, SPSC>::Peek(T* __restrict _dest, size_t _len) const
{
	if (!_len) return true;

	size_t h = m_head.load(std::memory_order_relaxed);
	size_t t = m_tail.load(std::memory_order_acquire);

	if (t - h < _len) return false;

	size_t idx = h & m_mask;

	if (_len >= 64)
	{
		_mm_prefetch((char*)&m_buffer[idx], _MM_HINT_T0);
		_mm_prefetch((char*)&m_buffer[0], _MM_HINT_T0);
	}

	size_t resume = m_capacity - idx;
	size_t first = _len < resume ? _len : resume;


	if constexpr (std::is_trivially_copyable_v<T>)
	{
		memcpy(_dest, &m_buffer[idx], first * sizeof(T));
		memcpy(_dest + first, &m_buffer[0], (_len - first) * sizeof(T));
	}
	else
	{
		std::copy_n(&m_buffer[idx], first, _dest);
		std::copy_n(&m_buffer[0], _len - first, _dest + first);
	}

	return true;
}

template<typename T>
size_t RingBuffer<T, SPSC>::Size() const
{
	return m_tail.load(std::memory_order_acquire) -
		m_head.load(std::memory_order_relaxed);
}