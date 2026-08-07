#ifndef __INCL_LYNTRA_NETWORK_QUIC_SOCKET_H__
#define __INCL_LYNTRA_NETWORK_QUIC_SOCKET_H__

#include "NetworkSocket.h"

namespace LyntraNet::Network::Socket
{
	typedef class NetworkQUICSocket
		QUIC_SOCK, * PQUIC_SOCK;

	class NetworkQUICSocket : public NetworkSocket
	{

	};
}
#endif
