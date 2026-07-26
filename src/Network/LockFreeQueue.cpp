#include <LyntraNet/Utility/LockFreeQueue.h>

using namespace LyntraNet::Utility;

template<typename T>
LockFreeQueue<T>::LockFreeQueue()
{

}

template<typename T>
void LockFreeQueue<T>::Enqueue(T* _obj)
{
	Node* node = new Node(_obj, nullptr);
	Node* h = m_head.load(std::memory_order_acquire);
	Node* t = m_tail.load(std::memory_order_acquire);

	do
	{
		if (t->prev == h)
		{
			node->prev = h;
			node->next = t;
		}
		else
		{

		}
	} while (!m_head.compare_exchange_weak(
		h,
		node,
		std::memory_order_release,
		std::memory_order_acquire));
}

template<typename T>
T* LockFreeQueue<T>::Dequeue()
{
	Node* h = m_head.load(std::memory_order_acquire);
	while (h->next)
	{
		Node* next = h->next;
		if (m_head.compare_exchange_weak(
			h,
			next,
			std::memory_order_acq_rel,
			std::memory_order_acquire
		))
		{

		}
	}
	return nullptr;
}
