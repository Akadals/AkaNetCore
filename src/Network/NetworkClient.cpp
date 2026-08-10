#include "LyntraNet/Network/NetworkClient.h"

using namespace LyntraNet::Network;

DWORD NetworkClient::Read()
{
	auto region =
		m_recvBuf.AcquireWriteRegion();
	if (region.Empty()) return 0;

	Packet::IOCONTEXT* ctx = m_sock->AcquireContext();

	memset(&ctx->m_overlapped, 0, sizeof(OVERLAPPED));
	ctx->m_ioType = Packet::IOTYPE::READING;

	ctx->m_wsaBuf[0].buf = 
		reinterpret_cast<char*>(region.firstPtr);
	ctx->m_wsaBuf[0].len = 
		static_cast<ULONG>(region.firstSize);
	ctx->m_wsaBuf[1].buf = 
		reinterpret_cast<char*>(region.secondPtr);
	ctx->m_wsaBuf[1].len =
		static_cast<ULONG>(region.secondSize);

	return m_sock->Read(*ctx);
}

DWORD NetworkClient::Write()
{
	return 0;
}
