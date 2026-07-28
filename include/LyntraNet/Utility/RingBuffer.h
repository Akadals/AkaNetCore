#pragma once
#include "ConcurrentPolicy.h"
#include <atomic>
#include <memory>

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

		alignas(64) mutable std::atomic<size_t> m_head = 0;
		alignas(64) mutable std::atomic<size_t> m_tail = 0;
	public:
		RingBuffer<SPSC>(size_t _size);
		bool Push(const std::byte* __restrict _dest, size_t _len);
		bool Pop(std::byte* __restrict _dest, size_t _len);
		bool Peek(std::byte* __restrict _dest, size_t _len) const;
		size_t Size() const;
		void Clear();
	};

	template<>
	class RingBuffer<MPSC>
	{
	private:

		size_t m_capacity;
		size_t m_mask;

		alignas(64) mutable std::atomic<size_t> m_head = 0;
		alignas(64) mutable std::atomic<size_t> m_tail = 0;
	public:
		RingBuffer<MPSC>(size_t _size);
	};

	template<>
	class RingBuffer<SPMC>
	{
	private:

		size_t m_capacity;
		size_t m_mask;

		alignas(64) mutable std::atomic<size_t> m_head = 0;
		alignas(64) mutable std::atomic<size_t> m_tail = 0;
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

		alignas(64) mutable std::atomic<size_t> m_head = 0;
		alignas(64) mutable std::atomic<size_t> m_tail = 0;
	public:
		RingBuffer<MPMC>(size_t _size);
	};
}

#include "Detail/RingBuffer/RingBufferSPSC.inl"
#include "Detail/RingBuffer/RingBufferMPSC.inl"
#include "Detail/RingBuffer/RingBufferSPMC.inl"
#include "Detail/RingBuffer/RingBufferMPMC.inl"