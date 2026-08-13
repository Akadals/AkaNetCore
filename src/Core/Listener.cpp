#include <LyntraNet/Core/Listener.h>

using namespace LyntraNet;

Listener::Listener(Protocol _protocol, ProtocolOption _protocolOpt)
{
	switch (_protocol)
	{
	case Protocol::TCP:
	case Protocol::UDP:
	case Protocol::KCP:
	case Protocol::QUIC:
	default: break;
	}
}

bool Listener::Startup(uint16_t _port)
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	size_t threadSize = static_cast<size_t>(sysInfo.dwNumberOfProcessors) * 2 + 1;

	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) return false;
	if ((m_hComPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0)) == NULL) return false;
	if ((m_listenSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET) return false;
	CreateIoCompletionPort((HANDLE)m_listenSock, m_hComPort, (ULONG_PTR)0, 0);

	memset(&m_listenAdr, 0, sizeof(m_listenAdr));

	m_listenAdr.sin_family = AF_INET;
	m_listenAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_listenAdr.sin_port = htons(_port);

	if (::bind(m_listenSock, (PSOCKADDR)&m_listenAdr, sizeof(m_listenAdr)) == SOCKET_ERROR) return false;

	if (listen(m_listenSock, 100) == SOCKET_ERROR) return false;

	LoadAcceptEx();

	for (int i = 0; i < 100; i++) PostAccept();
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

void Listener::OnAccept(Network::PIOCONTEXT _context)
{
	int sockLen = sizeof(m_listenSock);

	setsockopt(_context->m_ownerFd, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,
		(char*)&m_listenSock, sizeof(m_listenSock));

	SOCKADDR* localAdr = nullptr;
	SOCKADDR* remoteAdr = nullptr;

	int localAdrLen = 0;
	int remoteAdrLen = 0;

	DWORD dwLen = sizeof(SOCKADDR_IN) + 16;

	m_lpGetAcceptExSockaddrs(_context->m_wsaBuf[0].buf, 0, dwLen, dwLen,
		(PSOCKADDR*)&localAdr, &localAdrLen, (PSOCKADDR*)&remoteAdr, &remoteAdrLen);

	auto connection = m_ConnectionManager.AcquireConnection();
	auto transport = m_ConnectionManager.AcquireTransport();

	transport->SetSocket(m_ConnectionManager.AcquireSocket());
	connection->SetTransport(std::move(transport));

	connection->Bind(
		_context->m_ownerFd,
		*reinterpret_cast<SOCKADDR_IN*>(localAdr),
		*reinterpret_cast<SOCKADDR_IN*>(remoteAdr));

	CreateIoCompletionPort((HANDLE)_context->m_ownerFd, 0, NULL, 0);

	PostAccept();

	delete _context;
}
