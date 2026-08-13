#ifndef __INCL_LYNTRA_CORE_H__
#define __INCL_LYNTRA_CORE_H__

#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")

namespace LyntraNet
{
	class IOCPCore
	{
	private:
		DWORD WINAPI Worker(PVOID args);
	};
}
#endif