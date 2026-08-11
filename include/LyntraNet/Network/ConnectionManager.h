#ifndef __INCL_LYNTRA_CONNECTION_MANAGER_H__
#define __INCL_LYNTRA_CONNECTION_MANAGER_H__

#include <LyntraNet/Utility.h>
#include "NetworkConnection.h"
#include "Socket/NetworkSocket.h"
#include "Session.h"

namespace LyntraNet::Network
{
	class ConnectionManager
	{
	public:
		static const size_t CLIENT_POOL_SIZE = 65536;
		static const size_t SESSION_POOL_SIZE = 65536;
	private:
		LockFreePoolDynamic<NET_CONNECTION> m_connectionPool = { CLIENT_POOL_SIZE };
		LockFreePoolDynamic<Socket::NET_SOCK> m_socketPool = { CLIENT_POOL_SIZE };

#pragma region Game
		LockFreePoolDynamic<Game::SESSION> m_sessionPool = { SESSION_POOL_SIZE };
		ConcurrentHashMap<uint64_t, Game::SESSION, MPSC> m_userList;
#pragma endregion
	public:
		ConnectionManager();
		PNET_CONNECTION AcquireClient();
	};
}
#endif