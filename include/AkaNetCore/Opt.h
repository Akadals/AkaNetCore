#include <AkaNetCore/Core.h>
#include <filesystem>

#define OPT_LOGGER_TIME_FORMAT				((unsigned int)1 << 0)
#define OPT_LOGGER_ENABLE_FILE_OUTPUT		((unsigned int)1 << 1)
#define OPT_LOGGER_FILE_OUTPUT_PATH			((unsigned int)1 << 2)
#define OPT_LOGGER_LOGGING_LEVEL			((unsigned int)1 << 3)
#define OPT_LOGGER_ENABLE_COLORED			((unsigned int)1 << 4)

/*
#======================Option Type Requirements=====================#
|																	|
|	* OPT_LOGGER_TIME_FORMAT			:	std::string				|
|	* OPT_LOGGER_ENABLE_FILE_OUTPUT		:	bool					|
|	* OPT_LOGGER_FILE_OUTPUT_PATH		:	std::filesystem::path	|
|	* OPT_LOGGER_LOGGING_LEVEL			:	int						|
|	* OPT_LOGGER_ENABLE_COLORED			:	bool					|
|																	|
#===================================================================#
*/

namespace AkaNetCore
{
	void SetOpt(unsigned int opt, bool param);
	void SetOpt(unsigned int opt, std::filesystem::path param);
	void SetOpt(unsigned int opt, std::string param);
	void SetOpt(unsigned int opt, const char* param);
	void SetOpt(unsigned int opt, int param);
}