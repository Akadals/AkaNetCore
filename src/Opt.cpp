#include <AkaNetCore/Opt.h>
#include <AkaNetCore/Logger.h>
#include "Internal.h"

void AkaNetCore::SetOpt(unsigned int opt, bool param)
{
	auto ALLOW_FLAGS = 
		OPT_LOGGER_ENABLE_COLORED |
		OPT_LOGGER_ENABLE_FILE_OUTPUT;

	if (opt & ~ALLOW_FLAGS)
	{
		PRINT_ERROR("Unallowed bitflag option");
		return;
	}

	if (opt & OPT_LOGGER_ENABLE_COLORED)
		Internal::Logger::SetOptValue(OPT_LOGGER_ENABLE_COLORED, param);
	if (opt & OPT_LOGGER_ENABLE_FILE_OUTPUT)
		Internal::Logger::SetOptValue(OPT_LOGGER_ENABLE_FILE_OUTPUT, param);
}

void AkaNetCore::SetOpt(unsigned int opt, std::filesystem::path param)
{
	switch (opt)
	{
	case OPT_LOGGER_FILE_OUTPUT_PATH:
		Internal::Logger::SetOptValue(opt, param); 
		break;
	default:
		PRINT_ERROR("SetOpt type mismatch or Unallowed bitflag option");
		PRINT_DETAIL("The required type is std::filesystem::path");
		break;
	}
}

void AkaNetCore::SetOpt(unsigned int opt, std::string param)
{
	switch (opt)
	{
	case OPT_LOGGER_TIME_FORMAT: 
		Internal::Logger::SetOptValue(opt, param);
		break;
	default:
		PRINT_ERROR("SetOpt type mismatch or Unallowed bitflag option");
		PRINT_DETAIL("The required type is std::string"); 
		break;
	}
}

void AkaNetCore::SetOpt(unsigned int opt, const char* param)
{
	switch (opt)
	{
	case OPT_LOGGER_TIME_FORMAT:
		Internal::Logger::SetOptValue(opt, std::string(param)); 
		break;
	case OPT_LOGGER_FILE_OUTPUT_PATH:
		Internal::Logger::SetOptValue(opt, std::filesystem::path(param)); 
		break;
	default:
		PRINT_ERROR("SetOpt type mismatch or Unallowed bitflag option");
		PRINT_DETAIL("The required type is const char*");
		break;
	}
}

void AkaNetCore::SetOpt(unsigned int opt, int param)
{
	switch (opt)
	{
	case OPT_LOGGER_LOGGING_LEVEL:
		Internal::Logger::SetOptValue(opt, param);
		break;
	default:
		PRINT_ERROR("SetOpt type mismatch or Unallowed bitflag option");
		PRINT_DETAIL("The required type is int");
		break;
	}
}
