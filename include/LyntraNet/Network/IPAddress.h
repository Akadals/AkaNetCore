#ifndef __INCL_LYNTRA_IPADDRESS_H__
#define __INCL_LYNTRA_IPADDRESS_H__

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <sal.h>

namespace LyntraNet::Network
{
	class IPAddress
	{
	private:
		sockaddr_storage m_storage = {};
		socklen_t m_length = {};
	public:
		IPAddress() = default;

		void SetAddress(
			_In_reads_to_ptr_(_len) const sockaddr* _addr,
			_In_ socklen_t _len);

		ADDRESS_FAMILY Family() const;

		size_t Hash() const;

		bool IsIPv4() const;
		bool IsIPv6() const;
		bool IsLoopback() const;
		bool IsAny() const;
		bool IsBroadcast() const;
		bool IsMulticast() const;

		bool operator==(_In_ const IPAddress&) const;
		bool operator!=(_In_ const IPAddress&) const;

		const sockaddr* Data() const;
		sockaddr* Data();
		socklen_t Length() const;
		uint16_t Port() const;

		std::string ToString() const;
		std::string ToStringWithPort() const;

		static IPAddress AnyIPv4(_In_ uint16_t _port);
		static IPAddress AnyIPv6(_In_ uint16_t _port);

		static IPAddress LoopbackIPv4(_In_ uint16_t _port);
		static IPAddress LoopbackIPv6(_In_ uint16_t _port);

		static IPAddress Parse(
			_In_ std::string_view _ip, 
			_In_ uint16_t _port);
	};
}
#endif