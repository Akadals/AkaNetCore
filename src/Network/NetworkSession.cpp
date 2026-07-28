#include "LyntraNet/NetworkSession.h"

using namespace LyntraNet::Session;

NetworkSession::NetworkSession(SOCKET _socket, SOCKADDR_IN _addr)
	:m_sock(_socket), 
	m_sockAdr(_addr)
{
	inet_ntop(
		AF_INET, 
		&m_sockAdr.sin_addr, 
		m_sockAdrIp, 
		sizeof(m_sockAdrIp));
}

NetworkSession::~NetworkSession()
{}

DWORD NetworkSession::Read()
{
	auto region =
		m_recvBuf.AcquireWriteRegion();
	if (region.Empty()) return 0;

	Packet::PIOCONTEXT ctx;
	m_ioContext.Dequeue(ctx);
	ctx->Init();

	memset(&ctx->m_overlapped, 0, sizeof(OVERLAPPED));
	ctx->m_ioType = Packet::IOTYPE::READING;

	ctx->m_wsaBuf[0].buf = region.firstPtr;
	ctx->m_wsaBuf[0].len = region.firstSize;
	ctx->m_wsaBuf[1].buf = region.secondPtr;
	ctx->m_wsaBuf[1].len = region.secondSize;

	return WSARecv(
		m_sock, 
		ctx->m_wsaBuf, 
		region.secondSize > 0 ? 2 : 1,
		NULL, 
		&m_ioFlag, 
		&ctx->m_overlapped, 
		NULL);
}

DWORD NetworkSession::Write()
{
	return 0;
}

void NetworkSession::ParsePayload()
{
	while (true)
	{
		auto region = m_recvBuf.AcquireReadRegion();
		if (region.readableSize < sizeof(Packet::HEADER))
			return;

		Packet::HEADER header = {};

		size_t copied = 0;
		size_t copySize = std::min(
			region.firstSize,
			sizeof(Packet::HEADER));

		memcpy(
			&header,
			region.firstPtr,
			copySize);
		copied += copySize;

		if (copied < sizeof(Packet::HEADER))
		{
			memcpy(
				reinterpret_cast<char*>(&header) + copied,
				region.secondPtr,
				sizeof(Packet::HEADER) - copied);
		}

		size_t packetSize = sizeof(Packet::HEADER) + header.size;

		Parse(header);

		m_recvBuf.CommitRead(packetSize);
	}
}

void NetworkSession::Parse(Packet::HEADER _header)
{

}
