#include <LyntraNet/Core/Listener.h>

using namespace LyntraNet;

bool Listener::Startup()
{
	return false;
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

void Listener::PostAccept() const
{
	Packet::PIOCONTEXT ctx = new Packet::IOCONTEXT();

	if ((ctx->m_socket = WSASocket(
		AF_INET,
		SOCK_STREAM,
		0, NULL, 0,
		WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		delete ctx;
		return; //loging
	}

	ctx->m_ioType = Packet::IOTYPE::ACCEPT;

	DWORD bytes = 0;
	DWORD dwLen = sizeof(SOCKADDR_IN) + 16;

	if (!m_lpAcceptEx(m_listenSock, ctx->m_socket, ctx->m_wsaBuf[0].buf, 0,
		dwLen, dwLen, &bytes, &ctx->m_overlapped)) return; //loging
}

void Listener::OnAccept(Packet::PIOCONTEXT _context)
{
	int sockLen = sizeof(m_listenSock);

	setsockopt(_context->m_socket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,
		(char*)&m_listenSock, sizeof(m_listenSock));

	SOCKADDR* localAdr = nullptr;
	SOCKADDR* remoteAdr = nullptr;

	int localAdrLen = 0;
	int remoteAdrLen = 0;

	DWORD dwLen = sizeof(SOCKADDR_IN) + 16;

	m_lpGetAcceptExSockaddrs(_context->m_wsaBuf[0].buf, 0, dwLen, dwLen,
		(PSOCKADDR*)&localAdr, &localAdrLen, (PSOCKADDR*)&remoteAdr, &remoteAdrLen);

	Network::NetworkClient* client = m_clientManager.AcquireClient();

	client->AllocateSocket(
		_context->m_socket,
		*reinterpret_cast<SOCKADDR_IN*>(localAdr),
		*reinterpret_cast<SOCKADDR_IN*>(remoteAdr));

	CreateIoCompletionPort((HANDLE)_context->m_socket, 0, NULL, 0);

	PostAccept();

	delete _context;
}
