#ifndef __INCL_LYNTRA_NETWORK_CONNECTION_H__
#define __INCL_LYNTRA_NETWORK_CONNECTION_H__

#include <LyntraNet/Utility.h>
#include <LyntraNet/Packet.h>
#include <LyntraNet/Network/Transport/ITransport.h>

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <atomic>

namespace LyntraNet::Network
{
	typedef class NetworkConnection
		NET_CONNECTION, * PNET_CONNECTION;

	class alignas(64) NetworkConnection : 
		public std::enable_shared_from_this<NetworkConnection>
	{
	public:
		static const size_t RECV_BUF_SIZE = 8192;
		static const size_t SEND_BUF_SIZE = 8192;
	private:
		uint64_t connectionId;

		std::unique_ptr<Transport::ITransport> m_transport;

		RingBuffer<ZeroCopy> m_recvBuf = { RECV_BUF_SIZE };
		RingBuffer<ZeroCopy> m_sendBuf = { SEND_BUF_SIZE };

		DWORD m_timeoutTime;
	public:
		NetworkConnection() = default;

		void AllocateSocket(
			SOCKET _socket,
			const SOCKADDR_IN& _localAddr,
			const SOCKADDR_IN& _remoteAddr)
		{
			//m_sock->Allocate(_socket, _localAddr, _remoteAddr);
		}

		DWORD Read();
		DWORD Write();
	};
}
#endif