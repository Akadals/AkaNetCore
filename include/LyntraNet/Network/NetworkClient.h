#ifndef __INCL_LYNTRA_NETWORK_CLIENT_H__
#define __INCL_LYNTRA_NETWORK_CLIENT_H__

#include <LyntraNet/Utility.h>
#include <LyntraNet/Packet.h>
#include <LyntraNet/Network/Socket/NetworkSocket.h>
#include <LyntraNet/Network/Socket/NetworkTCPSocket.h>
#include <LyntraNet/Network/Socket/NetworkUDPSocket.h>
#include <LyntraNet/Network/Socket/NetworkRUDPSocket.h>
#include <LyntraNet/Network/Socket/NetworkQUICSocket.h>
#include <LyntraNet/Network/Socket/NetworkTLSSocket.h>

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
		static const size_t RECV_BUF_SIZE = 8192;
		static const size_t SEND_BUF_SIZE = 8192;
	private:
		std::unique_ptr<Socket::NetworkSocket> m_sock;

		RingBuffer<ZeroCopy> m_recvBuf = { RECV_BUF_SIZE };
		RingBuffer<ZeroCopy> m_sendBuf = { SEND_BUF_SIZE };
	public:
		NetworkClient() = default;

		void AllocateSocket(
			SOCKET _socket,
			const SOCKADDR_IN& _localAddr,
			const SOCKADDR_IN& _remoteAddr)
		{
			m_sock->Allocate(_socket, _localAddr, _remoteAddr);
		}

		DWORD Read();
		DWORD Write();
	};
}
#endif