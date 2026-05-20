#include <AkaNetCore/Job.h>

AkaNetCore::Job::Job()
{
	Init();
}

void AkaNetCore::Job::Init()
{
	ZeroMemory(&data, sizeof(vector<char>));
	header = 0;
}
