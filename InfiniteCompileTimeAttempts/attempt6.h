#pragma once

template <typename T>
struct Infinite5
{
    using inner = Infinite5<T>;
    static constexpr int value = Infinite5<inner>::value;
};