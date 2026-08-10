#ifndef __INCL_LYNTRA_NETWORK_TCP_SOCKET_H__
#define __INCL_LYNTRA_NETWORK_TCP_SOCKET_H__

#include "NetworkSocket.h"

namespace LyntraNet::Network::Socket
{
	typedef class NetworkTCPSocket
		TCP_SOCK, * PTCP_SOCK;

	class NetworkTCPSocket : public NetworkSocket
	{
		alignas(64) std::atomic<DWORD> m_ioCount = 0x80000000;
		alignas(64) DWORD m_ioFlag = 0;
	public:
		NetworkTCPSocket();

		DWORD Read(Packet::IOCONTEXT& _context) override;
		DWORD Write(Packet::IOCONTEXT& _context) override;
	};
}
#endif
