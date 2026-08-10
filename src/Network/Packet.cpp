#include <LyntraNet/Packet.h>

using namespace LyntraNet::Packet;
void LyntraNet::Packet::IOContext::Init()
{
	ZeroMemory(&m_overlapped, sizeof(OVERLAPPED));
	m_wsaBuf->buf = nullptr;
	m_wsaBuf->len = 0;
	m_ioType = IOType::READING;
}

IOContext::IOContext() { Init(); }
