#include "LyntraNet/Network/Socket/NetworkSocket.h"

using namespace LyntraNet::Network::Socket;

void NetworkSocket::Allocate(
	SOCKET _socket,
	const SOCKADDR_IN& _localAddr,
	const SOCKADDR_IN& _remoteAddr)
{
	m_sock = _socket;

	m_local.SetAddress(
		reinterpret_cast<const sockaddr*>(&_localAddr),
		sizeof(_localAddr));

	m_remote.SetAddress(
		reinterpret_cast<const sockaddr*>(&_remoteAddr),
		sizeof(_remoteAddr));
}
