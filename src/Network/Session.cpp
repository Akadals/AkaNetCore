#include <LyntraNet/Session.h>

using namespace LyntraNet::Session;

Session::Session(SOCKET socket, SOCKADDR_IN addr)
	:NetworkSession(socket, addr)
{

}

Session::~Session()
{}
