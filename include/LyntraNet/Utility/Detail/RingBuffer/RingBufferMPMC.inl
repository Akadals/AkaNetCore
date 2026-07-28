using namespace LyntraNet::Utility;

RingBuffer<MPMC>::RingBuffer<MPMC>(size_t _size)
{
	size_t cap = 1;
	while (cap < _size) cap <<= 1;

	m_mask = (m_capacity = cap) - 1;
	m_buffer = std::make_unique<Cell[]>(m_capacity);

	for (int i = 0; i < m_capacity; i++)
		m_buffer[i].m_sequence = i;
}