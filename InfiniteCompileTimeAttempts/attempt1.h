#pragma once

constexpr int infinite_loop(int ival) noexcept{
    return ival * infinite_loop(ival);
}