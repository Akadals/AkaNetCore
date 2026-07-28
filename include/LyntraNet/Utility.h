#include "Utility/RingBuffer.h"
#include "Utility/ConcurrentQueue.h"

#include "Utility/ConcurrentPolicy.h"

template<typename T>
using LockFreePool = LyntraNet::Utility::ConcurrentQueue<T, MPMC>;