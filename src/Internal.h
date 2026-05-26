#pragma once
#include <type_traits>

namespace AkaNetCore
{
	namespace Internal
	{
		namespace Logger
		{
			void SetColor(uint8_t color);
			std::string GetTimeStr();
			std::string LevelToString(LoggingLevel level);
			uint8_t LevelToColor(LoggingLevel level);
			void SetOptValueImpl(unsigned int opt, const void* param, const std::type_info& type);
			template<typename T>
			inline void SetOptValue(unsigned int opt, const T& param)
			{ SetOptValueImpl(opt, &param, typeid(T)); }
		}
		namespace Test
		{
			void SetOptValueImpl(unsigned int opt, const void* param, const std::type_info& type);
			template<typename T>
			inline void SetOptValue(unsigned int opt, const T& param)
			{ SetOptValueImpl(opt, &param, typeid(T)); }
		}
	}
}