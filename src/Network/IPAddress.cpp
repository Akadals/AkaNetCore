#include "LyntraNet/Network/IPAddress.h"

using namespace LyntraNet::Network;

IPAddress::IPAddress(const sockaddr* _addr, socklen_t _len)
{
	SetAddress(_addr, _len);
}

void IPAddress::SetAddress(const sockaddr * _addr, socklen_t _len)
{
	m_length = _len;
	memcpy(&m_storage, _addr, _len);
}

ADDRESS_FAMILY IPAddress::Family() const
{
	return m_storage.ss_family;
}

size_t IPAddress::Hash() const
{
	return size_t();
}

bool IPAddress::IsIPv4() const
{
	return Family() == AF_INET;
}

bool IPAddress::IsIPv6() const
{
	return Family() == AF_INET6;
}

bool IPAddress::IsLoopback() const
{
	return false;
}

bool IPAddress::IsAny() const
{
	return false;
}

bool IPAddress::IsBroadcast() const
{
	return false;
}

bool IPAddress::IsMulticast() const
{
	return false;
}

bool IPAddress::operator==(const IPAddress&) const
{
	return false;
}

bool IPAddress::operator!=(const IPAddress&) const
{
	return false;
}

const sockaddr* IPAddress::Data() const
{
	return reinterpret_cast<const sockaddr*>(&m_storage);
}

sockaddr* IPAddress::Data()
{
	return reinterpret_cast<sockaddr*>(&m_storage);
}

socklen_t IPAddress::Length() const
{
	return m_length;
}

uint16_t IPAddress::Port() const
{
	switch (Family())
	{
	case AF_INET:
		return ntohs(
			reinterpret_cast<const sockaddr_in*>
			(&m_storage)->sin_port);
	case AF_INET6:
		return ntohs(
			reinterpret_cast<const sockaddr_in6*>
			(&m_storage)->sin6_port);
	default: return 0;
	}
}

std::string IPAddress::ToString() const
{
	char buffer[INET6_ADDRSTRLEN]{};

	switch (Family())
	{
	case AF_INET:
		inet_ntop(
			AF_INET,
			&reinterpret_cast<const sockaddr_in*>
			(&m_storage)->sin_addr,
			buffer,
			sizeof(buffer));
		break;
	case AF_INET6:
		inet_ntop(
			AF_INET6,
			&reinterpret_cast<const sockaddr_in6*>
			(&m_storage)->sin6_addr,
			buffer,
			sizeof(buffer));
		break;
	default:
		strcpy_s(buffer, "Unknown");
		break;
	}

	return buffer;
}

std::string IPAddress::ToStringWithPort() const
{
	return ToString() + ":" + std::to_string(Port());
}

IPAddress IPAddress::AnyIPv4(uint16_t _port)
{
	return IPAddress();
}

IPAddress IPAddress::AnyIPv6(uint16_t _port)
{
	return IPAddress();
}

IPAddress IPAddress::LoopbackIPv4(uint16_t _port)
{
	return IPAddress();
}

IPAddress IPAddress::LoopbackIPv6(uint16_t _port)
{
	return IPAddress();
}

IPAddress IPAddress::Parse(std::string_view _ip, uint16_t _port)
{
	return IPAddress();
}
