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
	enum class Protocol
	{
		TCP,
		TCPWithTLS,
		UDP,
		QUIC,
		RUDP,
	}; //temp
	class Listener
	{
	private:
		HANDLE m_hComPort = {};

		SOCKET m_listenSock = { INVALID_SOCKET };
		SOCKADDR_IN m_listenAdr = {};

		LPFN_ACCEPTEX m_lpAcceptEx = {};
		LPFN_GETACCEPTEXSOCKADDRS m_lpGetAcceptExSockaddrs = {};

		Network::ConnectionManager m_ConnectionManager = {};
	public:
		Listener(Protocol _protocol = Protocol::TCP);
		bool Startup(uint16_t _port = 9000);
	private:
		void LoadAcceptEx();
		void PostAccept() const;
		void OnAccept(Packet::PIOCONTEXT _context);
	};
}
#endif