#ifndef __INCL_LYNTRA_IPENDPOINT_H__
#define __INCL_LYNTRA_IPENDPOINT_H__

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <sal.h>


namespace LyntraNet::Network
{
	class IPEndPoint
	{
	private:
		uint16_t m_port;
	public:
		IPEndPoint() = default;
		void GetPort() const noexcept { return m_port; }
	};
}
#endif