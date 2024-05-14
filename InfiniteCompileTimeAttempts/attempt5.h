#pragma once

template <typename T>
struct Infinite4
{
    using inner = Infinite4<Infinite4<T>>;
    static constexpr int value() {
        return inner::value();
    }
};