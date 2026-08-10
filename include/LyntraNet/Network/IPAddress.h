#ifndef __INCL_LYNTRA_IPADDRESS_H__
#define __INCL_LYNTRA_IPADDRESS_H__

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>

namespace LyntraNet::Network
{
	class IPAddress
	{
	private:
		sockaddr_storage m_storage = {};
		socklen_t m_length = {};
	public:
		IPAddress() = default;

		void SetAddress(const sockaddr* _addr, socklen_t _len);

		ADDRESS_FAMILY Family() const;

		size_t Hash() const;

		bool IsIPv4() const;
		bool IsIPv6() const;
		bool IsLoopback() const;
		bool IsAny() const;
		bool IsBroadcast() const;
		bool IsMulticast() const;

		bool operator==(const IPAddress&) const;
		bool operator!=(const IPAddress&) const;

		const sockaddr* Data() const;
		sockaddr* Data();
		socklen_t Length() const;
		uint16_t Port() const;

		std::string ToString() const;
		std::string ToStringWithPort() const;

		static IPAddress AnyIPv4(uint16_t _port);
		static IPAddress AnyIPv6(uint16_t _port);

		static IPAddress LoopbackIPv4(uint16_t _port);
		static IPAddress LoopbackIPv6(uint16_t _port);

		static IPAddress Parse(std::string_view _ip, uint16_t _port);
	};
}
#endif