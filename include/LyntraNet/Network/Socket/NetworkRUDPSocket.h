#ifndef __INCL_LYNTRA_NETWORK_RUDP_SOCKET_H__
#define __INCL_LYNTRA_NETWORK_RUDP_SOCKET_H__


#include "NetworkSocket.h"

namespace LyntraNet::Network::Socket
{
	typedef class NetworkRUDPSocket
		RUDP_SOCK, * PRUDP_SOCK;

	class NetworkRUDPSocket : public NetworkSocket
	{

	};
}
#endif
