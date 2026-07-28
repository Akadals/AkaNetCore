#ifndef __INCL_LYNTRA_CONCURRENT_POLICY_H__
#define __INCL_LYNTRA_CONCURRENT_POLICY_H__
#include <concepts>

struct SPSC {}; // Single-Producer Single-Consumer
struct MPSC {}; // Multi-Producer Single-Consumer
struct SPMC {}; // Single-Producer Multi-Consumer
struct MPMC {}; // Multi-Producer Multi-Consumer

template<typename T>
concept ConcurrentPolicy =
std::same_as<T, SPSC> ||
std::same_as<T, MPSC> ||
std::same_as<T, SPMC> ||
std::same_as<T, MPMC>;

#endif