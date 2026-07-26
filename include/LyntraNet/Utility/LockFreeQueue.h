#include <atomic>

namespace LyntraNet::Utility
{
	template<typename T>
	class LockFreeQueue
	{
	private:
		struct Node
		{
			T* data;
			Node* next;
			Node* prev;
		};
		std::atomic<Node*> m_head = { nullptr };
		std::atomic<Node*> m_tail = { nullptr };
	public:
		LockFreeQueue();
		void Enqueue(T* _obj);
		T* Dequeue();
	};
}
