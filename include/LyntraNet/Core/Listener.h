#ifndef __INCL_LYNTRA_LISTENER_H__
#define __INCL_LYNTRA_LISTENER_H__

#include <WinSock2.h>
#include <Windows.h>
#include <MSWSock.h>
#include <ws2tcpip.h>
#include <LyntraNet/Network/ConnectionManager.h>
#include <LyntraNet/Network/IOContext.h>
#include <LyntraNet/Network/IPEndPoint.h>
#include <LyntraNet/Network/Protocol.h>

namespace LyntraNet
{
	class ListenerBase
	{
	protected:
		SOCKET m_listenSock = { INVALID_SOCKET };
		Network::IPEndPoint m_localEndpoint = {};
	public:
		ListenerBase(const Network::IPEndPoint _endpoint)
		{ m_localEndpoint = _endpoint; }
		virtual bool Start() = 0;
	};

	template<TProtocol>
	class Listener;

	template<>
	class Listener<TCP> : public ListenerBase
	{
	private:
		LPFN_ACCEPTEX m_lpAcceptEx = {};
		LPFN_GETACCEPTEXSOCKADDRS m_lpGetAcceptExSockaddrs = {};
	public:
		Listener<TCP>(const Network::IPEndPoint _endpoint) :
			ListenerBase(_endpoint) {}

		void Listen(size_t _size);
	private:
		void LoadAcceptEx();
		void PostAccept();
	};
	template<>
	class Listener<UDP> : public ListenerBase
	{

	};
	template<>
	class Listener<QUIC> : public ListenerBase
	{

	};
	template<>
	class Listener<KCP> : public ListenerBase
	{

	};
}
#endif