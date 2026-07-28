using namespace LyntraNet::Utility;

RingBuffer<SPSC>::RingBuffer<SPSC>(size_t _size)
{
	size_t cap = 1;
	while (cap < _size) cap <<= 1;

	m_mask = (m_capacity = cap) - 1;
	m_buffer = std::make_unique<std::byte[]>(m_capacity);
}

bool RingBuffer<SPSC>::Push(const std::byte* __restrict _dest, size_t _len)
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

	memcpy(&m_buffer[idx], _dest, first);
	memcpy(&m_buffer[0], _dest + first, _len - first);

	m_tail.store(t + _len, std::memory_order_release);

	return true;
}

bool RingBuffer<SPSC>::Pop(std::byte* __restrict _dest, size_t _len)
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

	memcpy(_dest, &m_buffer[idx], first);
	memcpy(_dest + first, &m_buffer[0], _len - first);

	m_head.store(h + _len, std::memory_order_release);

	return true;
}

bool RingBuffer<SPSC>::Peek(std::byte* __restrict _dest, size_t _len) const
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

	memcpy(_dest, &m_buffer[idx], first);
	memcpy(_dest + first, &m_buffer[0], _len - first);

	return true;
}

size_t RingBuffer<SPSC>::Size() const
{
	return m_tail.load(std::memory_order_acquire) -
		m_head.load(std::memory_order_relaxed);
}