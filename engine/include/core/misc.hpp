#ifndef __MISC_HPP__
#define __MISC_HPP__

#include <chrono>
#include <stdlib.h>

namespace rss
{
    template <typename T>
    inline T min(T a, T b)
    {
        return a < b ? a : b;
    }

    template <typename T>
    inline T min(T a, T b, T c)
    {
        return min(min(a, b), c);
    }

    template <typename T>
    inline T max(T a, T b)
    {
        return a > b ? a : b;
    }

    template <typename T>
    inline T max(T a, T b, T c)
    {
        return max(max(a, b), c);
    }

    template <typename T>
    inline int sign(T x)
    {
        return x > 0 ? 1 : (x < 0 ? -1 : 0);
    }

    template <typename T>
    inline T abs(T x)
    {
        return x >= 0 ? x : -x;
    }

    template <typename T>
    inline T sq(T x)
    {
        return x * x;
    }

    inline double randf()
    {
        return double(rand()) / double(RAND_MAX);
    }

    inline int64_t ms()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }
}

#endif