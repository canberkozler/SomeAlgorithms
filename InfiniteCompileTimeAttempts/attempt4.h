#pragma once

template<size_t N>
struct Infinite3
{
    static constexpr size_t value = Infinite3<N - 1>::value;
};

template<size_t N>
struct Infinite3_Helper
{
    static constexpr size_t value = Infinite3_Helper<N - 1>::value;
};

template<>
struct Infinite3<0>
{
    static constexpr size_t value = Infinite3_Helper<100>::value;
};

template<>
struct Infinite3_Helper<0>
{
    static constexpr size_t value = Infinite3<100>::value;
};
