#include <LyntraNet/Core/LyntraServer.h>

using namespace LyntraNet;

template<TProtocol T>
Utility::LyntraErrorObject LyntraServer::AddListener(const Network::IPEndPoint& _endpoint)
{
	auto listener = std::make_unique<Listener<T>>(_endpoint);
	m_listeners.emplace_back(std::move(listener));
	return LyntraErrorObject();
}
template<TProtocol T>
Utility::LyntraErrorObject LyntraServer::AddListener(const Network::IPAddress& _address, uint16_t _port)
{
	auto listener = std::make_unique<Listener<T>>(
		Network::IPEndPoint(_address, _port));
	m_listeners.emplace_back(std::move(listener));
	return LyntraErrorObject();
}
template<TProtocol T>
Utility::LyntraErrorObject LyntraServer::AddListener(uint16_t _port)
{
	auto listener = std::make_unique<Listener<T>>(
		Network::IPEndPoint(
			Network::IPAddress::AnyIPv4, _port));
	m_listeners.emplace_back(std::move(listener));
	return LyntraErrorObject();
}

Utility::LyntraErrorObject LyntraServer::Start()
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return Utility::LyntraErrorObject();

	return Utility::LyntraErrorObject();
}
