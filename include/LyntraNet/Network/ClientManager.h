#ifndef __INCL_LYNTRA_CLIENT_MANAGER_H__
#define __INCL_LYNTRA_CLIENT_MANAGER_H__

#include <LyntraNet/Utility.h>
#include "NetworkClient.h"

namespace LyntraNet::Network
{
	class ClientManager
	{
	public:
		static const size_t CLIENT_POOL_SIZE = 65536;
	private:
		LockFreePoolDynamic<NetworkClient> m_clientPool = { CLIENT_POOL_SIZE };
	public:
		ClientManager();
		NetworkClient* AcquireClient();
	};
}
#endif