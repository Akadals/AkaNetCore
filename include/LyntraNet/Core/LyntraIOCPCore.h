#ifndef __INCL_LYNTRA_CORE_H__
#define __INCL_LYNTRA_CORE_H__

#include "Listener.h"

#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")

namespace LyntraNet
{
	class Core
	{
	private:
		HANDLE m_iocp;

		std::vector<std::unique_ptr<Listener>> m_listener;
		Network::ConnectionManager m_connectionManager;

		std::atomic<bool> isRunning = false;
	public:
		Core();
		void Startup();
	private:
		DWORD WINAPI Worker(PVOID args);
	};
}
#endif



// 헤더명 변경 예정