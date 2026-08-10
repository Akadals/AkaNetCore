#ifndef __INCL_LYNTRA_PACKET_H__
#define __INCL_LYNTRA_PACKET_H__

#include "Utility/ConcurrentPolicy.h"
#include <winsock2.h>
#include <atomic>
#include <vector>

namespace LyntraNet::Packet
{
	typedef enum class IOType : uint8_t
	{ READING, WRITING, ACCEPT }
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
		SOCKET m_socket = { INVALID_SOCKET };
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
}
#endif