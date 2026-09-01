#ifndef __INCL_LYNTRA_PROTOCOL_H__
#define __INCL_LYNTRA_PROTOCOL_H__
#include <concepts>

struct TCP {};
struct UDP {};
struct KCP {};
struct QUIC {};

template<typename T>
concept TProtocol =
std::same_as<T, TCP> ||
std::same_as<T, UDP> ||
std::same_as<T, QUIC> ||
std::same_as<T, KCP>;

#endif