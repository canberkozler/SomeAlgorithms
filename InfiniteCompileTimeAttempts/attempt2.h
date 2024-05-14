#pragma once

template<size_t N>
struct Infinite1
{
    static constexpr std::size_t value = Infinite1<N + 1>::value;
};
