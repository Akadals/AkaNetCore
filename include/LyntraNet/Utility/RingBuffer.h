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
		std::unique_ptr<std::byte[]> m_buffer;

		size_t m_capacity;
		size_t m_mask;

		mutable CacheLineAtomic m_reserveHead;
		mutable CacheLineAtomic m_publishHead;

		mutable CacheLineAtomic m_reserveTail;
		mutable CacheLineAtomic m_publishTail;
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

		mutable CacheLineCached m_producer;
		mutable CacheLineCached m_consumer;
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
	template<>
	class RingBuffer<ZeroCopy>
	{
	public:
		struct Region
		{
			std::byte* firstPtr = nullptr;
			size_t firstSize = 0;
			std::byte* secondPtr = nullptr;
			size_t secondSize = 0;

			Region(
				std::byte* _firstPtr,
				size_t _firstSize,
				std::byte* _secondPtr,
				size_t _secondSize) :
				firstPtr(_firstPtr),
				firstSize(_firstSize),
				secondPtr(_secondPtr),
				secondSize(_secondSize) {}

			bool Empty() const
			{
				return firstSize + secondSize == 0;
			}
		};
		struct WriteRegion : public Region
		{
			size_t writableSize = 0;
			WriteRegion(
				std::byte* _firstPtr,
				size_t _firstSize,
				std::byte* _secondPtr,
				size_t _secondSize,
				size_t _writableSize) :
				Region(
					_firstPtr,
					_firstSize,
					_secondPtr,
					_secondSize),
				writableSize(_writableSize) {}
		};
		struct ReadRegion : public Region
		{
			size_t readableSize = 0;
			ReadRegion(
				std::byte* _firstPtr,
				size_t _firstSize,
				std::byte* _secondPtr,
				size_t _secondSize,
				size_t _readableSize) :
				Region(
					_firstPtr,
					_firstSize,
					_secondPtr,
					_secondSize),
				readableSize(_readableSize) {}
		};
	private:
		std::unique_ptr<std::byte[]> m_buffer;

		size_t m_capacity;
		size_t m_mask;

		mutable CacheLineAtomic m_head;
		mutable CacheLineAtomic m_tail;
	public:
		RingBuffer<ZeroCopy>(size_t _size);

		WriteRegion AcquireWriteRegion();
		ReadRegion AcquireReadRegion();

		void CommitWrite(size_t _size);
		void CommitRead(size_t _size);
	};
}

#include "Detail/RingBuffer/RingBufferSPSC.inl"
#include "Detail/RingBuffer/RingBufferMPSC.inl"
#include "Detail/RingBuffer/RingBufferSPMC.inl"
#include "Detail/RingBuffer/RingBufferMPMC.inl"
#include "Detail/RingBuffer/RingBufferFastSPSC.inl"
#include "Detail/RingBuffer/RingBufferZeroCopy.inl"
#endif