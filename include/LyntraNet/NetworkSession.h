#include "Utility.h"
#include "Packet.h"

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <mutex>
#include <atomic>

namespace LyntraNet::Session
{
	typedef class NetworkSession 
		NET_SESSION, * PNET_SESSION;
	class alignas(64) NetworkSession
	{
	public:
		static const size_t RECV_BUF_SIZE = 65536;
		static const size_t SEND_BUF_SIZE = 65536;
		static const size_t IO_CONTEXT_POOL_SIZE = 512;
	private:
		SOCKET m_sock = {};
		SOCKADDR_IN m_sockAdr = {};
		char m_sockAdrIp[INET_ADDRSTRLEN] = {};

		Packet::RingBuffer m_recvBuf = { RECV_BUF_SIZE };
		Packet::RingBuffer m_sendBuf = { SEND_BUF_SIZE };

		Utility::LockFreeQueue<Packet::IOCONTEXT> m_ioContext = {};

		alignas(64) std::atomic <DWORD> m_ioCount = 0x80000000;
		alignas(64) DWORD m_ioFlag = 0;
	public:
		NetworkSession(SOCKET _socket, SOCKADDR_IN _addr);
		~NetworkSession();

		SOCKET GetSocket() const { return m_sock; }
		const char* GetIPAddress() const { return m_sockAdrIp; }

		DWORD Read();
		DWORD Write();

		void ParsePayload();
		void Parse(Packet::HEADER _header);
	};
}