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
		static const size_t CONNECTION_POOL_SIZE = 1024;
		static const size_t SESSION_POOL_SIZE = 1024;
	private:
		LockFreePool<std::unique_ptr<NET_CONNECTION>>
			m_connectionPool = { CONNECTION_POOL_SIZE };
		LockFreePool<std::unique_ptr<Transport::ITransport>>
			m_transportPool = { CONNECTION_POOL_SIZE };
		LockFreePool<std::unique_ptr<Socket::NET_SOCK>> 
			m_socketPool = { CONNECTION_POOL_SIZE };

#pragma region Network Session
		ConcurrentHashMap<uint64_t, std::unique_ptr<NET_CONNECTION>, MPSC>
			m_connections;
		ConcurrentHashMap<SOCKET, uint64_t, MPSC>
			m_socketMap;
#pragma endregion

#pragma region Game Session
#ifdef _USE_GAME_SESSION_
		LockFreePool<Game::SESSION> m_sessionPool = { SESSION_POOL_SIZE };
		ConcurrentHashMap<uint64_t, Game::SESSION, MPSC> m_userList;
#endif
#pragma endregion
	public:
		ConnectionManager();
		PNET_CONNECTION AcquireClient();
	};
}
#endif