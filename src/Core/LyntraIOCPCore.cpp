#include <LyntraNet/Core/LyntraIOCPCore.h>
using namespace LyntraNet;

HANDLE hComPort;

DWORD __stdcall IOCPCore::Worker(PVOID args)
{
	DWORD byteTrans = 0;
	ULONG_PTR completionKey = 0;
	LPOVERLAPPED overlappedPtr = nullptr;
	BOOL res = false;

	while (true)
	{
		byteTrans = 0;
		completionKey = 0;
		overlappedPtr = nullptr;

		res = GetQueuedCompletionStatus(hComPort, &byteTrans, &completionKey, &overlappedPtr, INFINITE);
		if (!overlappedPtr)
		{
			//shutdown
			if (!completionKey)
			{
			}
			else
			{
				//logging
			}
			continue;
		}

		if (overlappedPtr == (LPOVERLAPPED)0xffffffff)
		{
			//disconnect
			continue;
		}

		if (res)
		{
		}
	}
	return 0;
}