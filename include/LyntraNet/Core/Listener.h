#include <WinSock2.h>
#include <Windows.h>
#include <MSWSock.h>
#include <ws2tcpip.h>

#include <LyntraNet/Network/NetworkClient.h>
#include <LyntraNet/Network/ClientManager.h>

namespace LyntraNet
{
	class Listener
	{
	private:
		SOCKET m_listenSock = { INVALID_SOCKET };

		LPFN_ACCEPTEX m_lpAcceptEx = {};
		LPFN_GETACCEPTEXSOCKADDRS m_lpGetAcceptExSockaddrs = {};

		Network::ClientManager m_clientManager = {};
	public:
		Listener() = default;
		bool Startup();
	private:
		void LoadAcceptEx();
		void PostAccept() const;
		void OnAccept(Packet::PIOCONTEXT _context);
	};
}