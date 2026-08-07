#include <WinSock2.h>
#include <Windows.h>
#include <MSWSock.h>
#include <ws2tcpip.h>

//#include "../Network/NetworkSocket.h"

namespace LyntraNet
{
	class Listener
	{
	private:
		//Network::NET_SOCK listenSock;

		LPFN_ACCEPTEX lpAcceptEx = {};
		LPFN_GETACCEPTEXSOCKADDRS lpGetAcceptExSockaddrs = {};
	public:
		bool Startup();
	private:
		void LoadAcceptEx();
		void PostAccept();
	};
}