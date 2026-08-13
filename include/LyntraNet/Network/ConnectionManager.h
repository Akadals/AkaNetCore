#ifndef __INCL_LYNTRA_CONNECTION_MANAGER_H__
#define __INCL_LYNTRA_CONNECTION_MANAGER_H__

#include <LyntraNet/Utility.h>
#include "NetworkConnection.h"
#include "Socket/NetworkSocket.h"
#include "Session.h"

#include <LyntraNet/Network/IOContext.h>

namespace LyntraNet::Network
{
	class ConnectionManager
	{
	public:
		static const size_t CONNECTION_POOL_SIZE = 1024;
		static const size_t SESSION_POOL_SIZE = 1024;
		static const size_t ACCEPT_CONTEXT_POOL_SIZE = 100;
		static const size_t JOB_POOL_SIZE = 65565;
	private:
		LockFreePool<std::unique_ptr<NET_CONNECTION>>
			m_connectionPool = { CONNECTION_POOL_SIZE };
		LockFreePool<std::unique_ptr<Transport::ITransport>>
			m_transportPool = { CONNECTION_POOL_SIZE };
		LockFreePool<std::unique_ptr<Socket::NET_SOCK>> 
			m_socketPool = { CONNECTION_POOL_SIZE };

		LockFreePool<PIOCONTEXT, ACCEPT_CONTEXT_POOL_SIZE>
			m_acceptCtxPool;

		//LockFreePool<Packet::JOB> m_JobPool = { JOB_POOL_SIZE };

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
		std::unique_ptr<NET_CONNECTION> AcquireConnection() 
		{ return m_connectionPool.Acquire(); }
		std::unique_ptr<Transport::ITransport> AcquireTransport()
		{ return m_transportPool.Acquire(); }
		std::unique_ptr<Socket::NET_SOCK> AcquireSocket()
		{ return m_socketPool.Acquire(); }
		PIOCONTEXT AcquireAcceptCtx()
		{ return m_acceptCtxPool.Acquire(); }
	};
}
#endif