#include "LyntraNet/Network/NetworkClient.h"

using namespace LyntraNet::Network;

DWORD NetworkClient::Read()
{
	auto region =
		m_recvBuf.AcquireWriteRegion();
	if (region.Empty()) return 0;

	auto ctx = m_ioContext.Acquire();
	ctx->Init();

	memset(&ctx->m_overlapped, 0, sizeof(OVERLAPPED));
	ctx->m_ioType = Packet::IOTYPE::READING;

	ctx->m_wsaBuf[0].buf = region.firstPtr;
	ctx->m_wsaBuf[0].len = region.firstSize;
	ctx->m_wsaBuf[1].buf = region.secondPtr;
	ctx->m_wsaBuf[1].len = region.secondSize;

	return WSARecv(
		m_sock.GetSocket(),
		ctx->m_wsaBuf, 
		region.secondSize > 0 ? 2 : 1,
		NULL, 
		&m_ioFlag, 
		&ctx->m_overlapped, 
		NULL);
}

DWORD NetworkClient::Write()
{
	return 0;
}

void Socket::NetworkSocket::SetLocal()
{
	sockaddr_storage addr{};
	int size = sizeof(addr);

	getsockname(
		m_sock,
		reinterpret_cast<sockaddr*>(&addr),
		&size);

	m_local.SetAddress(
		reinterpret_cast<sockaddr*>(&addr),
		size);
}
