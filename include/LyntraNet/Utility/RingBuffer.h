#ifndef __INCL_LYNTRA_RING_BUFFER_H__
#define __INCL_LYNTRA_RING_BUFFER_H__

#include "ConcurrentPolicy.h"
#include "../Memory.h"
#include <atomic>
#include <memory>
#include <span>

namespace LyntraNet::Utility
{
	template<ConcurrentPolicy>
	class RingBuffer;

	template<>
	class RingBuffer<SPSC>
	{
	private:
		std::unique_ptr<std::byte[]> m_buffer;

		size_t m_capacity;
		size_t m_mask;

		mutable CacheLineAtomic m_head;
		mutable CacheLineAtomic m_tail;
	public:
		RingBuffer<SPSC>(size_t _size);

		template<size_t ByteSize>
		bool TryWrite(const std::byte* __restrict _src);
		bool TryWrite(const std::byte* __restrict _src, size_t _len);
		bool TryWrite(std::span<const std::byte> _src);

		template<size_t ByteSize>
		bool TryRead(std::byte* __restrict _dest);
		bool TryRead(std::byte* __restrict _dest, size_t _len);
		bool TryRead(std::span<std::byte> _dest);

		template<size_t ByteSize>
		void ReadPreview(std::byte* __restrict _dest) const;
		void ReadPreview(std::byte* __restrict _dest, size_t _len) const;
		void ReadPreview(std::span<std::byte> _dest) const;

		void Clear();

		size_t Size() const noexcept;
		size_t Capacity() const { return m_capacity; }
	};

	template<>
	class RingBuffer<MPSC>
	{
	private:

		size_t m_capacity;
		size_t m_mask;

		mutable CacheLineAtomic m_head;
		mutable CacheLineAtomic m_tail;
	public:
		RingBuffer<MPSC>(size_t _size);
	};

	template<>
	class RingBuffer<SPMC>
	{
	private:
		size_t m_capacity;
		size_t m_mask;

		mutable CacheLineAtomic m_head;
		mutable CacheLineAtomic m_tail;
	public:
		RingBuffer<SPMC>(size_t _size);
	};
	
	template<>
	class RingBuffer<MPMC>
	{
	private:
		struct Cell
		{
			std::atomic<size_t> m_sequence;
			std::byte m_data;
		};
		std::unique_ptr<Cell[]> m_buffer;

		size_t m_capacity;
		size_t m_mask;

		mutable CacheLineAtomic m_head;
		mutable CacheLineAtomic m_tail;
	public:
		RingBuffer<MPMC>(size_t _size);

		bool TryWrite(const std::byte* __restrict _src, size_t _len);
		bool TryWrite(std::span<const std::byte> _src);

		bool TryRead(std::byte* __restrict _dest, size_t _len);
		bool TryRead(std::span<std::byte> _dest);

		void ReadPreview(std::byte* __restrict _dest, size_t _len) const;
		void ReadPreview(std::span<std::byte> _dest) const;

		void Clear();

		size_t Size() const noexcept;
		size_t Capacity() const { return m_capacity; }
	};
	template<>
	class RingBuffer<FastSPSC>
	{
	private:
		std::unique_ptr<std::byte[]> m_buffer;

		size_t m_capacity;
		size_t m_mask;

		mutable UnsafeProducer m_producer;
		mutable UnsafeConsumer m_consumer;
	public:
		RingBuffer<FastSPSC>(size_t _size);

		template<size_t ByteSize>
		bool TryWrite(const std::byte* __restrict _src);
		bool TryWrite(const std::byte* __restrict _src, size_t _len);
		bool TryWrite(std::span<const std::byte> _src);

		template<size_t ByteSize>
		bool TryRead(std::byte* __restrict _dest);
		bool TryRead(std::byte* __restrict _dest, size_t _len);
		bool TryRead(std::span<std::byte> _dest);

		template<size_t ByteSize>
		void ReadPreview(std::byte* __restrict _dest) const;
		void ReadPreview(std::byte* __restrict _dest, size_t _len) const;
		void ReadPreview(std::span<std::byte> _dest) const;

		void Clear();

		size_t Size() const noexcept;
		size_t Capacity() const { return m_capacity; }
	};
}

#include "Detail/RingBuffer/RingBufferSPSC.inl"
#include "Detail/RingBuffer/RingBufferMPSC.inl"
#include "Detail/RingBuffer/RingBufferSPMC.inl"
#include "Detail/RingBuffer/RingBufferMPMC.inl"
#include "Detail/RingBuffer/RingBufferFastSPSC.inl"
#endif