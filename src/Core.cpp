#include <AkaNetCore/Core.h>
#include <AkaNetCore/Logger.h>

void AkaNetCore::SetOpt(UINT8 opt, OptParam param)
{
	switch (opt)
	{
	case OPT_LOGGER_TIME_FORMAT: Logger::s_timeFormat = get<const char*>(param); break;
	case OPT_LOGGER_ENABLE_FILE_OUTPUT: Logger::s_enableFileOutput = get<bool>(param); break;
	case OPT_LOGGER_FILE_OUTPUT_PATH: Logger::s_OutputPath = get<const char*>(param); break;
	}
}
