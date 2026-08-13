#include <iostream>
#include <LyntraNet/LyntraNet.h>

using namespace LyntraNet;

Listener serv1(Protocol::TCP);
Listener serv2(Protocol::UDP);
Listener serv3(Protocol::QUIC);
Listener serv4(Protocol::RUDP);

int main()
{
	serv1.Startup();
	serv2.Startup(9001);
	serv3.Startup(9002);
	serv4.Startup(9003);
}