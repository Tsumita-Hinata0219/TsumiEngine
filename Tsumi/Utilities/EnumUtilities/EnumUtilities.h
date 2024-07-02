#pragma once

#include <type_traits>

// Enumのサイズを取得するメタ関数
template<typename E, typename = void>
struct EnumSize;

template<typename E>
struct EnumSize<E, std::void_t<decltype(E::Count)>> {
    static constexpr std::size_t value = static_cast<std::size_t>(E::Count);
};

