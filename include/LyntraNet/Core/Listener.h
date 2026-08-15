#ifndef __INCL_LYNTRA_LISTENER_H__
#define __INCL_LYNTRA_LISTENER_H__

#include <WinSock2.h>
#include <Windows.h>
#include <MSWSock.h>
#include <ws2tcpip.h>

#include <LyntraNet/Network/NetworkConnection.h>
#include <LyntraNet/Network/ConnectionManager.h>
#include <LyntraNet/Core/LyntraIOCPCore.h>
#include <LyntraNet/Network/IOContext.h>
#include <LyntraNet/Network/IPEndPoint.h>

namespace LyntraNet
{
	enum class Protocol
	{
		TCP,
		UDP,
		QUIC,
		KCP,
	}; //юс╫ц enum class

	struct ProtocolOption
	{
		Network::Socket::SocketOption m_sockOpt;
	};

	class Listener
	{
	private:
		Protocol m_protocol = Protocol::TCP;
		Network::IPEndPoint m_endpoint = {};

		SOCKET m_listenSock = { INVALID_SOCKET };
		SOCKADDR_IN m_listenAdr = {};

		LPFN_ACCEPTEX m_lpAcceptEx = {};
		LPFN_GETACCEPTEXSOCKADDRS m_lpGetAcceptExSockaddrs = {};
	public:
		Listener(
			_In_ Protocol _protocol = Protocol::TCP,
			_In_ ProtocolOption _option = {}
		);
		void Bind(Network::IPEndPoint _endPoint);
		Protocol GetProtocol() const noexcept { return m_protocol; }
		SOCKET* GetSocket() { return &m_listenSock; }
		SOCKADDR_IN* GetSockAdr() { return &m_listenAdr; }
	private:
		void LoadAcceptEx();
		void PostAccept();
	};
}
#endif