#include <LyntraNet/Core/Listener.h>

using namespace LyntraNet;

bool Listener::Startup()
{
	return false;
}

void Listener::LoadAcceptEx()
{
	/*DWORD bytes = 0;
	auto loadExtension = [&](GUID guid, void** fnPtr)
		{ WSAIoctl(listenSock, SIO_GET_EXTENSION_FUNCTION_POINTER,
			&guid, sizeof(guid), fnPtr, sizeof(*fnPtr),
			&bytes, NULL, NULL); };

	loadExtension(WSAID_ACCEPTEX, 
		reinterpret_cast<void**>(&lpAcceptEx));
	loadExtension(WSAID_GETACCEPTEXSOCKADDRS, 
		reinterpret_cast<void**>(&lpGetAcceptExSockaddrs));*/
}

void Listener::PostAccept()
{

}
