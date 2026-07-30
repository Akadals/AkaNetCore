using namespace LyntraNet::Utility;

RingBuffer<FastSPSC>::RingBuffer<FastSPSC>(size_t _size)
{
	if (_size == 0) throw;

	size_t cap = 1;
	while (cap < _size) cap <<= 1;

	m_mask = (m_capacity = cap) - 1;
	m_buffer = std::make_unique<std::byte[]>(m_capacity);
}

template<size_t ByteSize>
bool RingBuffer<FastSPSC>::TryWrite(const std::byte* __restrict _src)
{
	static_assert(ByteSize > 0);
	if constexpr (ByteSize > 256)
		return TryWrite(_src, ByteSize);
	else
	{
		size_t t = m_producer.tail;

		if ((t + ByteSize) - m_producer.cachedHead > m_capacity) [[unlikely]]
		{
			m_producer.cachedHead = m_consumer.head;
			if ((t + ByteSize) - m_producer.cachedHead > m_capacity) [[unlikely]]
				return false;
		}

		size_t idx = t & m_mask;

		const size_t remaining = m_capacity - idx;

		std::byte* buffer = m_buffer.get();

		if (remaining >= ByteSize)
			Memory::Copy<ByteSize>(buffer + idx, _src);
		else [[unlikely]]
		{
			Memory::Copy(buffer + idx, _src, remaining);
			Memory::Copy(buffer, _src + remaining, ByteSize - remaining);
		}

		m_producer.tail += ByteSize;

		return true;
	}
}

bool RingBuffer<FastSPSC>::TryWrite(const std::byte* __restrict _src, size_t _len)
{
	if (_len == 0) [[unlikely]]
		return true;

	size_t t = m_producer.tail;

	if ((t + _len) - m_producer.cachedHead > m_capacity) [[unlikely]]
	{
		m_producer.cachedHead = m_consumer.head;
		if ((t + _len) - m_producer.cachedHead > m_capacity) [[unlikely]]
			return false;
	}

	size_t idx = t & m_mask;

	const size_t remaining = m_capacity - idx;
	size_t first = _len < remaining ? _len : remaining;

	std::byte* buffer = m_buffer.get();

	Memory::Copy(buffer + idx, _src, first);
	if (_len > remaining) [[unlikely]]
		Memory::Copy(buffer, _src + first, _len - first);

	m_producer.tail += _len;

	return true;
}

bool RingBuffer<FastSPSC>::TryWrite(std::span<const std::byte> _src)
{
	size_t len = _src.size();

	size_t t = m_producer.tail;

	if ((t + len) - m_producer.cachedHead > m_capacity) [[unlikely]]
	{
		m_producer.cachedHead = m_consumer.head;
		if ((t + len) - m_producer.cachedHead > m_capacity) [[unlikely]]
			return false;
	}

	size_t idx = t & m_mask;

	const size_t remaining = m_capacity - idx;
	size_t first = len < remaining ? len : remaining;

	std::byte* buffer = m_buffer.get();
	const std::byte* src = _src.data();

	Memory::Copy(buffer + idx, src, first);
	if (len > remaining) [[unlikely]]
		Memory::Copy(buffer, src + first, len - first);

	m_producer.tail += len;

	return true;
}

template<size_t ByteSize>
bool RingBuffer<FastSPSC>::TryRead(std::byte* __restrict _dest)
{
	static_assert(ByteSize > 0);
	if constexpr (ByteSize > 256)
		return TryRead(_dest, ByteSize);
	else
	{
		size_t h = m_consumer.head;

		if (m_consumer.cachedTail - h < ByteSize) [[unlikely]]
		{
			m_consumer.cachedTail = m_producer.tail;
			if (m_consumer.cachedTail - h < ByteSize) [[unlikely]]
				return false;
		}

		size_t idx = h & m_mask;

		const size_t remaining = m_capacity - idx;

		std::byte* buffer = m_buffer.get();

		if (remaining >= ByteSize)
			Memory::Copy<ByteSize>(_dest, buffer + idx);
		else [[unlikely]]
		{
			Memory::Copy(_dest, buffer + idx, remaining);
			Memory::Copy(_dest + remaining, buffer, ByteSize - remaining);
		}

		m_consumer.head += ByteSize;
		return true;
	}
}

bool RingBuffer<FastSPSC>::TryRead(std::byte* __restrict _dest, size_t _len)
{
	if (_len == 0) [[unlikely]]
		return true;

	size_t h = m_consumer.head;

	if (m_consumer.cachedTail - h < _len) [[unlikely]]
	{
		m_consumer.cachedTail = m_producer.tail;
		if (m_consumer.cachedTail - h < _len) [[unlikely]]
			return false;
	}

	size_t idx = h & m_mask;

	const size_t remaining = m_capacity - idx;
	size_t first = _len < remaining ? _len : remaining;
	
	std::byte* buffer = m_buffer.get();

	Memory::Copy(_dest, buffer + idx, first);
	if (_len > remaining) [[unlikely]]
		Memory::Copy(_dest + first, buffer, _len - first);

	m_consumer.head += _len;

	return true;
}

bool RingBuffer<FastSPSC>::TryRead(std::span<std::byte> _dest)
{
	size_t len = _dest.size();

	size_t h = m_consumer.head;

	if (m_consumer.cachedTail - h < len) [[unlikely]]
	{
		m_consumer.cachedTail = m_producer.tail;
		if (m_consumer.cachedTail - h < len) [[unlikely]]
			return false;
	}

	size_t idx = h & m_mask;

	const size_t remaining = m_capacity - idx;
	size_t first = len < remaining ? len : remaining;

	std::byte* buffer = m_buffer.get();
	std::byte* dest = _dest.data();

	Memory::Copy(dest, buffer + idx, first);
	if (len > remaining) [[unlikely]]
		Memory::Copy(dest + first, buffer, len - first);

	m_consumer.head += len;

	return true;
}

template<size_t ByteSize>
void RingBuffer<FastSPSC>::ReadPreview(std::byte* __restrict _dest) const
{
	static_assert(ByteSize > 0);
	if constexpr (ByteSize > 256)
		return ReadPreview(_dest, ByteSize);
	else
	{
		size_t h = m_consumer.head;

		if (m_consumer.cachedTail - h < ByteSize) [[unlikely]]
		{
			m_consumer.cachedTail = m_producer.tail;
			if (m_consumer.cachedTail - h < ByteSize) [[unlikely]]
				return;
		}

		size_t idx = h & m_mask;

		const size_t remaining = m_capacity - idx;

		std::byte* buffer = m_buffer.get();

		if (remaining >= ByteSize)
			Memory::Copy<ByteSize>(_dest, buffer + idx);
		else [[unlikely]]
		{
			Memory::Copy(_dest, buffer + idx, remaining);
			Memory::Copy(_dest + remaining, buffer, ByteSize - remaining);
		}
	}
}

void RingBuffer<FastSPSC>::ReadPreview(std::byte* __restrict _dest, size_t _len) const
{
	if (_len == 0) [[unlikely]]
		return;

	size_t h = m_consumer.head;

	if (m_consumer.cachedTail - h < _len) [[unlikely]]
	{
		m_consumer.cachedTail = m_producer.tail;
		if (m_consumer.cachedTail - h < _len) [[unlikely]]
			return;
	}

	size_t idx = h & m_mask;

	const size_t remaining = m_capacity - idx;
	size_t first = _len < remaining ? _len : remaining;

	std::byte* buffer = m_buffer.get();

	Memory::Copy(_dest, buffer + idx, first);
	if (_len > remaining) [[unlikely]]
		Memory::Copy(_dest + first, buffer, _len - first);
}

void RingBuffer<FastSPSC>::ReadPreview(std::span<std::byte> _dest) const
{
	size_t len = _dest.size();

	size_t h = m_consumer.head;

	if (m_consumer.cachedTail - h < len) [[unlikely]]
	{
		m_consumer.cachedTail = m_producer.tail;
		if (m_consumer.cachedTail - h < len) [[unlikely]]
			return;
	}

	size_t idx = h & m_mask;

	const size_t remaining = m_capacity - idx;
	size_t first = len < remaining ? len : remaining;

	std::byte* buffer = m_buffer.get();
	std::byte* dest = _dest.data();

	Memory::Copy(dest, buffer + idx, first);
	if (len > remaining) [[unlikely]]
		Memory::Copy(dest + first, buffer, len - first);
}

void RingBuffer<FastSPSC>::Clear()
{
	m_consumer.head = m_producer.tail;
	m_producer.cachedHead = m_consumer.cachedTail;
}

size_t RingBuffer<FastSPSC>::Size() const noexcept
{
	const size_t t = m_producer.tail;
	const size_t h = m_consumer.head;
	return t - h;
}