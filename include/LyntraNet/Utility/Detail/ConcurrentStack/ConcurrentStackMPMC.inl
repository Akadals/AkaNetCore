using namespace LyntraNet::Utility;

template<typename T>
ConcurrentStack<T, MPMC>::ConcurrentStack(size_t _size)
{
	size_t cap = 1;
	while (cap < _size) cap <<= 1;

	m_mask = (m_capacity = cap) - 1;
	m_buffer = std::make_unique<T[]>(m_capacity);

	for (int i = 0; i < m_capacity; i++)
		m_buffer[i].m_sequence = i;
}