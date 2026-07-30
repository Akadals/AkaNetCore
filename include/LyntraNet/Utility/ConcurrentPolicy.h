#ifndef __INCL_LYNTRA_CONCURRENT_POLICY_H__
#define __INCL_LYNTRA_CONCURRENT_POLICY_H__
#include <concepts>
#include <atomic>
#include <new>

#ifdef __cpp_lib_hardware_interference_size
#define CACHE_SIZE std::hardware_destructive_interference_size
#endif

struct SPSC {}; // Single-Producer Single-Consumer
struct MPSC {}; // Multi-Producer Single-Consumer
struct SPMC {}; // Single-Producer Multi-Consumer
struct MPMC {}; // Multi-Producer Multi-Consumer

struct FastSPSC {}; // Fast Single-Producer Single-Consumer (Non-atomic)

template<typename T>
concept ConcurrentPolicy =
std::same_as<T, SPSC> ||
std::same_as<T, MPSC> ||
std::same_as<T, SPMC> ||
std::same_as<T, MPMC> ||
std::same_as<T, FastSPSC>;

struct alignas(CACHE_SIZE) CacheLineAtomic
{
public:
    std::atomic<size_t> value = 0;
private:
	char padding[CACHE_SIZE - sizeof(std::atomic<size_t>)]{};
};
static_assert(sizeof(CacheLineAtomic) == CACHE_SIZE);
static_assert(alignof(CacheLineAtomic) == CACHE_SIZE);

#pragma region Unsafe
struct UnsafeProducer
{
    alignas(64) size_t tail = 0;
    size_t cachedHead = 0;
};


struct UnsafeConsumer
{
    alignas(64) size_t head = 0;
    size_t cachedTail = 0;
};
#pragma endregion
#endif