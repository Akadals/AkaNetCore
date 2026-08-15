#include <LyntraNet/Core/Listener.h>

using namespace LyntraNet;
Listener::Listener(Protocol _protocol, ProtocolOption _option)
{
	LoadAcceptEx();
}


void Listener::LoadAcceptEx()
{
	DWORD bytes = 0;
	auto loadExtension = [&](GUID guid, void** fnPtr)
		{ WSAIoctl(m_listenSock, SIO_GET_EXTENSION_FUNCTION_POINTER,
			&guid, sizeof(guid), fnPtr, sizeof(*fnPtr),
			&bytes, NULL, NULL); };

	loadExtension(WSAID_ACCEPTEX, 
		reinterpret_cast<void**>(&m_lpAcceptEx));
	loadExtension(WSAID_GETACCEPTEXSOCKADDRS, 
		reinterpret_cast<void**>(&m_lpGetAcceptExSockaddrs));
}

void Listener::PostAccept()
{
	auto ctx = m_ConnectionManager.AcquireAcceptCtx();

	if ((ctx->m_ownerFd = WSASocket(
		AF_INET,
		SOCK_STREAM,
		0, NULL, 0,
		WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		delete ctx;
		return; //loging
	}

	ctx->m_ioType = Network::IOTYPE::ACCEPT;

	DWORD bytes = 0;
	DWORD dwLen = sizeof(SOCKADDR_IN) + 16;

	if (!m_lpAcceptEx(m_listenSock, ctx->m_ownerFd, ctx->m_wsaBuf[0].buf, 0,
		dwLen, dwLen, &bytes, &ctx->m_overlapped)) return; //loging
}

//void Listener::OnAccept(Network::PIOCONTEXT _context)
//{
//	int sockLen = sizeof(m_listenSock);
//
//	setsockopt(_context->m_ownerFd, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,
//		(char*)&m_listenSock, sizeof(m_listenSock));
//
//	SOCKADDR* localAdr = nullptr;
//	SOCKADDR* remoteAdr = nullptr;
//
//	int localAdrLen = 0;
//	int remoteAdrLen = 0;
//
//	DWORD dwLen = sizeof(SOCKADDR_IN) + 16;
//
//	m_lpGetAcceptExSockaddrs(_context->m_wsaBuf[0].buf, 0, dwLen, dwLen,
//		(PSOCKADDR*)&localAdr, &localAdrLen, (PSOCKADDR*)&remoteAdr, &remoteAdrLen);
//
//	auto connection = m_ConnectionManager.AcquireConnection();
//	auto transport = m_ConnectionManager.AcquireTransport();
//
//	transport->SetSocket(m_ConnectionManager.AcquireSocket());
//	connection->SetTransport(std::move(transport));
//
//	connection->Bind(
//		_context->m_ownerFd,
//		*reinterpret_cast<SOCKADDR_IN*>(localAdr),
//		*reinterpret_cast<SOCKADDR_IN*>(remoteAdr));
//
//	CreateIoCompletionPort((HANDLE)_context->m_ownerFd, 0, NULL, 0);
//
//	PostAccept();
//
//	delete _context;
//}
