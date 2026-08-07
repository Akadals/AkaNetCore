#ifndef __INCL_LYNTRA_NETWORK_CLIENT_H__
#define __INCL_LYNTRA_NETWORK_CLIENT_H__

#include <LyntraNet/Utility.h>
#include <LyntraNet/Packet.h>
#include <LyntraNet/Network/Socket/NetworkSocket.h>

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <atomic>

namespace LyntraNet::Network
{
	typedef class NetworkClient
		NET_CLIENT, * PNET_CLIENT;

	class alignas(64) NetworkClient
	{
	public:
		static const size_t RECV_BUF_SIZE = 4096;
		static const size_t SEND_BUF_SIZE = 4096;
		static const size_t IO_CONTEXT_POOL_SIZE = 128;
	private:
		Socket::NetworkSocket m_sock;

		Packet::RingBuffer m_recvBuf = { RECV_BUF_SIZE };
		Packet::RingBuffer m_sendBuf = { SEND_BUF_SIZE };

		LockFreePool<Packet::IOCONTEXT> m_ioContext = { IO_CONTEXT_POOL_SIZE };

		alignas(64) std::atomic<DWORD> m_ioCount = 0x80000000;
		alignas(64) DWORD m_ioFlag = 0;
	public:
		NetworkClient(SOCKET _socket, const SOCKADDR_IN& _addr) :
			m_sock(_socket, _addr) {}
		Socket::NetworkSocket operator->() { return m_sock; }

		DWORD Read();
		DWORD Write();
	};
}
#endif