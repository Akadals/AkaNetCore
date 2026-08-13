#ifndef __INCL_LYNTRA_LISTENER_H__
#define __INCL_LYNTRA_LISTENER_H__

#include <WinSock2.h>
#include <Windows.h>
#include <MSWSock.h>
#include <ws2tcpip.h>

#include <LyntraNet/Network/NetworkConnection.h>
#include <LyntraNet/Network/ConnectionManager.h>
#include <LyntraNet/Core/LyntraIOCPCore.h>
#include <LyntraNet/Network/IOContext.h>

namespace LyntraNet
{
	enum class Protocol
	{
		TCP,
		UDP,
		QUIC,
		KCP,
	}; //임시 enum class

	struct ProtocolOption
	{
		// 보안 및 세부 프로토콜 옵션 추가 (ex. SocketOption)
	};

	class Listener
	{
	private:
		HANDLE m_hComPort = {};

		SOCKET m_listenSock = { INVALID_SOCKET };
		SOCKADDR_IN m_listenAdr = {};

		LPFN_ACCEPTEX m_lpAcceptEx = {};
		LPFN_GETACCEPTEXSOCKADDRS m_lpGetAcceptExSockaddrs = {};

		Network::ConnectionManager m_ConnectionManager = {};

		IOCPCore core;
	public:
		Listener(
			_In_opt_ Protocol _protocol = Protocol::TCP,
			_In_opt_ ProtocolOption _protocolOpt = {});
		bool Startup(_In_opt_ uint16_t _port = 9000);
	private:
		void LoadAcceptEx();
		void PostAccept();
		void OnAccept(_In_ Network::PIOCONTEXT _context);
	};
}
#endif