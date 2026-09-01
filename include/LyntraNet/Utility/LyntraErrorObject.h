#ifndef __INCL_LYNTRA_ERROR_HANDLER_H__
#define __INCL_LYNTRA_ERROR_HANDLER_H__

#include <string>

namespace LyntraNet::Utility
{
	class LyntraErrorObject
	{
	private:
		uint16_t m_statusCode = 0;
		std::string m_message;
	public:
		LyntraErrorObject() = default;

		uint16_t StatusCode() const noexcept { return m_statusCode; }
		std::string_view Message() const { return m_message; }
	};
}

#endif