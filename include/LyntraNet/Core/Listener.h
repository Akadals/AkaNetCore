#ifndef __INCL_LYNTRA_LISTENER_H__
#define __INCL_LYNTRA_LISTENER_H__

#include <WinSock2.h>
#include <Windows.h>
#include <MSWSock.h>
#include <ws2tcpip.h>

#include <LyntraNet/Network/NetworkConnection.h>
#include <LyntraNet/Network/ConnectionManager.h>

namespace LyntraNet
{
	class Listener
	{
	private:
		HANDLE m_hComPort = {};

		SOCKET m_listenSock = { INVALID_SOCKET };
		SOCKADDR_IN m_listenAdr = {};

		LPFN_ACCEPTEX m_lpAcceptEx = {};
		LPFN_GETACCEPTEXSOCKADDRS m_lpGetAcceptExSockaddrs = {};

		Network::ConnectionManager m_clientManager = {};
	public:
		Listener() = default;
		bool Startup();
	private:
		void LoadAcceptEx();
		void PostAccept() const;
		void OnAccept(Packet::PIOCONTEXT _context);
	};
}
#endif