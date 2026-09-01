#include <iostream>
#include <LyntraNet/LyntraNet.h>

using namespace LyntraNet::Network;

int main()
{
	LyntraNet::LyntraServer server;

	server.AddListener<TCP>(IPAddress::AnyPort());
	server.AddListener<UDP>(IPEndPoint(
		IPAddress::AnyIPv4(),
		IPAddress::AnyPort()));
	server.AddListener<KCP>(
		IPAddress::AnyIPv4(),
		IPAddress::AnyPort());
}