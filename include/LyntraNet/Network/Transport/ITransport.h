#ifndef __INCL_LYNTRA_ITRANSPORT_H__
#define __INCL_LYNTRA_ITRANSPORT_H__

#include <LyntraNet/Network/Socket/NetworkSocket.h>

namespace LyntraNet::Network::Transport
{
	class ITransport
	{
	private:
		std::unique_ptr<Socket::NetworkSocket> m_sock;
	public:
		void SetSocket(std::unique_ptr<Socket::NetworkSocket> _sock);
		Socket::NetworkSocket& GetSocket() const { return *m_sock; }
	};
}
#endif