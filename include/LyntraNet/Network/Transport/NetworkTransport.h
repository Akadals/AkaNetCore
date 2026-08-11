#ifndef __INCL_LYNTRA_NETWORK_TRANSPORT_H__
#define __INCL_LYNTRA_NETWORK_TRANSPORT_H__

#include <LyntraNet/Network/Socket/NetworkSocket.h>

namespace LyntraNet::Network::Transport
{
	class NetworkTransport
	{
	private:
		std::unique_ptr<Socket::NetworkSocket> m_sock;
	public:
		void SetSocket(std::unique_ptr<Socket::NetworkSocket> _sock);
	};
}
#endif