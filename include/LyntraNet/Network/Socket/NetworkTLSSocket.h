#ifndef __INCL_LYNTRA_NETWORK_TLS_SOCKET_H__
#define __INCL_LYNTRA_NETWORK_TLS_SOCKET_H__


#include "NetworkSocket.h"

namespace LyntraNet::Network::Socket
{
	typedef class NetworkTLSSocket
		RTLS_SOCK, * PTLS_SOCK;

	class NetworkTLSSocket : public NetworkSocket
	{

	};
}
#endif
