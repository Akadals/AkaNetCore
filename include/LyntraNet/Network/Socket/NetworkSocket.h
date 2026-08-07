#ifndef __INCL_LYNTRA_NETWORK_SOCKET_H__
#define __INCL_LYNTRA_NETWORK_SOCKET_H__

#include <WinSock2.h>
#include <WS2tcpip.h>

#include <LyntraNet/Network/IPAddress.h>


namespace LyntraNet::Network::Socket
{
	class NetworkSocket
	{
	protected:
		SOCKET m_sock = INVALID_SOCKET;

		IPAddress m_local;
		IPAddress m_remote;
	public:
		NetworkSocket(SOCKET _socket, const SOCKADDR_IN& _addr) :
			m_sock(_socket),
			m_remote(reinterpret_cast<const sockaddr*>(&_addr),
				sizeof(_addr)) {}

		SOCKET GetSocket() const { return m_sock; }

		const IPAddress& GetLocal() const { return m_local; }
		const IPAddress& GetRemote() const { return m_remote; }
	private:
		void SetLocal();
	};
}
#endif