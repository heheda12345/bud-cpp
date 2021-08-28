#pragma once

#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>

template <typename T>
struct second_param;

template <template <typename, typename, typename...> class C,
          typename T1,
          typename T2,
          typename... Ts>
struct second_param<C<T1, T2, Ts...>> {
    using type = T2;
};

template <class T>
class Timer {
 public:
    Timer() { clear(); }

    using Duration =
        decltype(std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::system_clock::now() -
            std::chrono::system_clock::now()));

    void clear() {
        this->mn = std::numeric_limits<Duration>::max();
        this->mx = this->sum = Duration::zero();
        this->cnt = 0;
    }

    void start() { this->start_time = std::chrono::system_clock::now(); }

    float end() {
        auto end_time = std::chrono::system_clock::now();
        return cast(end_time - this->start_time);
    }

    void log() {
        Duration duration = end();
        this->mn = std::min(this->mn, duration);
        this->mx = std::max(this->mx, duration);
        this->sum += duration;
        this->cnt += 1;
    }

    float get_min() const { return cast(mn); }
    float get_max() const { return cast(mx); }
    float get_sum() const { return cast(sum); }
    float get_avg() const { return cast(sum) / cnt; }
    int get_cnt() const { return cnt; }

 private:
    Duration mn, mx, sum;
    int cnt;
    std::chrono::time_point<std::chrono::system_clock> start_time;

    static float cast(Duration d) {
        return (d * 1e-9).count() * second_param<T>::type::den /
               second_param<T>::type::num;
    }
};