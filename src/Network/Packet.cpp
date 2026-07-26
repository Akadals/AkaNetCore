#include <LyntraNet/Packet.h>

using namespace LyntraNet::Packet;

RingBuffer::RingBuffer(size_t _size)
{
	size_t cap = 1;
	while (cap < _size) cap <<= 1;

	m_mask = (m_capacity = cap) - 1;
	m_buf.resize(m_capacity);
}

void LyntraNet::Packet::IOContext::Init()
{
	ZeroMemory(&m_overlapped, sizeof(OVERLAPPED));
	m_wsaBuf->buf = nullptr;
	m_wsaBuf->len = 0;
	m_ioType = IOType::READING;
}

IOContext::IOContext() { Init(); }

RingBuffer::WriteRegion RingBuffer::AcquireWriteRegion()
{
	size_t h = m_head.load(std::memory_order_acquire);
	size_t t = m_tail.load(std::memory_order_relaxed);

	size_t readable = t - h;
	size_t writable = m_capacity - readable;

	size_t headIdx = h & m_mask;
	size_t tailIdx = t & m_mask;

	size_t contiguous = 
		(tailIdx >= headIdx)
		? (m_capacity - tailIdx)
		: (headIdx - tailIdx);
	size_t size =
		std::min(writable, contiguous);

	return
	{
		&m_buf[tailIdx],
		size,
		&m_buf[0],
		writable - size,
		writable
	};
}

RingBuffer::ReadRegion RingBuffer::AcquireReadRegion()
{
	size_t h = m_head.load(std::memory_order_relaxed);
	size_t t = m_tail.load(std::memory_order_acquire);

	size_t readable = t - h;

	size_t headIdx = h & m_mask;
	size_t tailIdx = t & m_mask;

	size_t contiguous =
		(tailIdx >= headIdx)
		? tailIdx - headIdx
		: m_capacity - headIdx;

	size_t size =
		std::min(readable, contiguous);

	return 
	{ 
		&m_buf[headIdx],
		size,
		&m_buf[0],
		readable - size,
		readable
	};
}

void RingBuffer::CommitWrite(size_t _size)
{
	size_t tail = m_tail.load(std::memory_order_relaxed);
	m_tail.store(tail + _size, std::memory_order_release);
}

void RingBuffer::CommitRead(size_t _size)
{
	size_t head = m_head.load(std::memory_order_relaxed);
	m_head.store(head + _size, std::memory_order_release);
}
