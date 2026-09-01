#ifndef __INCL_LYNTRA_SERVER_H__
#define __INCL_LYNTRA_SERVER_H__

#include <memory>
#include <vector>
#include <atomic>
#include <LyntraNet/Network/IPEndPoint.h>
#include <LyntraNet/Network/Protocol.h>
#include <LyntraNEt/Core/Listener.h>
#include <LyntraNet/Utility/LyntraErrorObject.h>

namespace LyntraNet
{
	class LyntraServer
	{
	public:
		static const size_t MAX_LISTENER_SIZE = 10;
	private:
		std::vector<std::unique_ptr<ListenerBase>> m_listeners;
		std::atomic<bool> m_isRunning = false;
	public:
		LyntraServer() = default;

		Utility::LyntraErrorObject Start();
		Utility::LyntraErrorObject Stop();
		void Wait();

		template<TProtocol T> 
		Utility::LyntraErrorObject AddListener(const Network::IPEndPoint& _endpoint);
		template<TProtocol T> 
		Utility::LyntraErrorObject AddListener(const Network::IPAddress& _address, uint16_t _port);
		template<TProtocol T> 
		Utility::LyntraErrorObject AddListener(uint16_t _port);
	};
}

#endif