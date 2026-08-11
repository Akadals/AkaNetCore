#ifndef __INCL_LYNTRA_NETWORK_SOCKET_H__
#define __INCL_LYNTRA_NETWORK_SOCKET_H__

#include <WinSock2.h>
#include <WS2tcpip.h>

#include <LyntraNet/Network/IPAddress.h>
#include <LyntraNet/Utility.h>
#include <LyntraNet/Packet.h>


namespace LyntraNet::Network::Socket
{
	typedef class NetworkSocket
		NET_SOCK, * PNET_SOCK;

	class NetworkSocket
	{
	public:
		static const size_t IO_CONTEXT_POOL_SIZE = 128;
	protected:
		SOCKET m_sock = INVALID_SOCKET;

		IPAddress m_local;
		IPAddress m_remote;
	protected:
		LockFreePoolStatic<Packet::IOCONTEXT> m_ioContextPool = { IO_CONTEXT_POOL_SIZE };
	public:
		NetworkSocket() = default;

		void Allocate(
			SOCKET _socket, 
			const SOCKADDR_IN& _localAddr,
			const SOCKADDR_IN& _remoteAddr);

		SOCKET GetSocket() const { return m_sock; }

		const IPAddress& GetLocal() const { return m_local; }
		const IPAddress& GetRemote() const { return m_remote; }

		Packet::IOCONTEXT* AcquireContext() 
		{ return m_ioContextPool.Acquire(); }
		void ReleaseContext(Packet::IOCONTEXT* _context) 
		{ m_ioContextPool.Release(_context); }

		virtual DWORD Read(Packet::IOCONTEXT& _context) = 0;
		virtual DWORD Write(Packet::IOCONTEXT& _context) = 0;
	};
}
#endif