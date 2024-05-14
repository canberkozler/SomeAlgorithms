#pragma once

template<size_t N>
struct Infinite2
{
    enum{value = (N & 1) ? Infinite2<N-1>::value : Infinite2<N+1>::value};
};
