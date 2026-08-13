#include <LyntraNet/Network/IOContext.h>

using namespace LyntraNet::Network;
void IOContext::Init()
{
	ZeroMemory(&m_overlapped, sizeof(OVERLAPPED));
	m_wsaBuf->buf = nullptr;
	m_wsaBuf->len = 0;
	m_ioType = IOType::READING;
	m_ownerFd = INVALID_SOCKET;
}

IOContext::IOContext() { Init(); }