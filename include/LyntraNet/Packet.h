#ifndef __INCL_LYNTRA_PACKET_H__
#define __INCL_LYNTRA_PACKET_H__

#include <winsock2.h>
#include <atomic>
#include <vector>

namespace LyntraNet::Packet
{
	typedef enum class IOType : uint8_t
	{ READING, WRITING }
	IOTYPE;

	typedef struct Header
		HEADER, * PHEADER;
	typedef class IOContext
		IOCONTEXT, * PIOCONTEXT;
	typedef class Job
		JOB, * PJOB;

	#pragma pack(push, 1)
	struct Header
	{
		uint16_t size = 0;
		uint32_t header = 0;
	};
	#pragma pack(pop)

	class alignas(64) IOContext
	{
	public:
		OVERLAPPED m_overlapped = {};
		WSABUF m_wsaBuf[2] = {};
		IOTYPE m_ioType = {};
	public:
		IOContext();
		void Init();
	};

	class alignas(64) Job
	{
	private:
		std::vector<char> m_data;
		uint32_t m_header;
	};

	class alignas(64) RingBuffer
	{
	public:
		struct Region
		{
			char* firstPtr = nullptr;
			size_t firstSize = 0;
			char* secondPtr = nullptr;
			size_t secondSize = 0;

			Region(
				char* _firstPtr,
				size_t _firstSize,
				char* _secondPtr,
				size_t _secondSize) :
				firstPtr(_firstPtr),
				firstSize(_firstSize),
				secondPtr(_secondPtr),
				secondSize(_secondSize) {}

			bool Empty() const
			{ return firstSize + secondSize == 0; }
		};
		struct WriteRegion : public Region
		{
			size_t writableSize = 0;
			WriteRegion(
				char* _firstPtr,
				size_t _firstSize,
				char* _secondPtr,
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
				char* _firstPtr,
				size_t _firstSize,
				char* _secondPtr,
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
		std::unique_ptr<char[]> m_buf;

		size_t m_capacity = 0;
		size_t m_mask = 0;

		mutable alignas(64) std::atomic<size_t> m_head = 0;
		mutable alignas(64) std::atomic<size_t> m_tail = 0;
	public:
		RingBuffer(size_t _size);

		WriteRegion AcquireWriteRegion();
		ReadRegion AcquireReadRegion();

		void CommitWrite(size_t _size);
		void CommitRead(size_t _size);
	};
}
#endif