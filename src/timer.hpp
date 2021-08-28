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

    using Duration = decltype((std::chrono::system_clock::now() -
                               std::chrono::system_clock::now()));

    void clear() {
        this->mn = Duration::max();
        this->mx = this->sum = Duration::zero();
        this->cnt = 0;
    }

    void start() { this->start_time = std::chrono::system_clock::now(); }

    float end() {
        auto end_time = std::chrono::system_clock::now();
        return cast(end_time - this->start_time);
    }

    void log() {
        auto end_time = std::chrono::system_clock::now();
        Duration duration = end_time - this->start_time;
        this->mn = std::min(this->mn, duration);
        this->mx = std::max(this->mx, duration);
        this->sum += duration;
        this->cnt += 1;
    }

    void report() const { std::cout << *this << std::endl; }

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
        return (d * 1.0 * second_param<Duration>::type::num /
                second_param<Duration>::type::den)
                   .count() *
               second_param<T>::type::den / second_param<T>::type::num;
    }
};

template <class T>
inline std::ostream& operator<<(std::ostream& os, const Timer<T>& timer) {
    os << timer.get_cnt() << " iters, avg = " << timer.get_avg()
       << ", min = " << timer.get_min() << ", max = " << timer.get_max();
    return os;
}