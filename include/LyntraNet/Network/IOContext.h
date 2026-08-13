#ifndef __INCL_LYNTRA_IOCONTEXT_H__
#define __INCL_LYNTRA_IOCONTEXT_H__

#include <winsock2.h>

namespace LyntraNet::Network
{
	typedef enum class IOType : uint8_t
	{ READING, WRITING, ACCEPT } IOTYPE;

	typedef class IOContext
		IOCONTEXT, * PIOCONTEXT;

	class alignas(64) IOContext
	{
	public:
		OVERLAPPED m_overlapped = {};
		WSABUF m_wsaBuf[2] = {};
		IOTYPE m_ioType = {};
		SOCKET m_ownerFd = { INVALID_SOCKET };
	public:
		IOContext();
		void Init();
	};
}
#endif