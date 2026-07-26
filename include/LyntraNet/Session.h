#include "NetworkSession.h"

namespace LyntraNet::Session
{
	typedef class Session
		SESSION, * PSESSION;

	class alignas(64) Session : public NetworkSession
	{
	public:
		static const size_t MAX_NAME_SIZE = 30;
	private:
		DWORD m_uid = {};
		char m_uuid[37] = {};

		char m_nickname[MAX_NAME_SIZE] = {};
	public:
		Session(SOCKET _socket, SOCKADDR_IN _addr);
		~Session();
		DWORD GetUID() const { return m_uid; }
		const char* GetUUID() const { return m_uuid; }
		const char* GetNickname() const { return m_nickname; }
	};
}