#include <gtest/gtest.h>
#include <chrono>
#include <cstdio>
#include <timer.hpp>
using namespace std;
using namespace chrono;

template <class T>
void mock_sleep(int ns) {
    auto start_time = chrono::system_clock::now();
    while (true) {
        auto end_time = chrono::system_clock::now();
        if (duration_cast<T>(end_time - start_time).count() > ns) {
            return;
        }
    }
}

#define expect_near(result_, mock, err)    \
    {                                      \
        result = result_;                  \
        EXPECT_GE(result, mock);           \
        EXPECT_LT(result, mock*(1 + err)); \
    }

TEST(TimerTest, BeginEnd) {
    Timer<nanoseconds> t_nano;
    float result;

    t_nano.start();
    mock_sleep<microseconds>(1000);
    expect_near(t_nano.end();, 1e6, 0.01);

    t_nano.start();
    mock_sleep<microseconds>(2000);
    expect_near(t_nano.end(), 2e6, 0.01);

    Timer<microseconds> t_micro;

    t_micro.start();
    mock_sleep<microseconds>(3000);
    expect_near(t_micro.end(), 3e3, 0.01);

    t_micro.start();
    mock_sleep<microseconds>(4000);
    expect_near(t_micro.end(), 4e3, 0.01);

    Timer<seconds> t_sec;
    t_sec.start();
    mock_sleep<microseconds>(5000);
    expect_near(t_sec.end(), 5e-3, 0.01);

    t_sec.start();
    mock_sleep<microseconds>(6000);
    expect_near(t_sec.end(), 6e-3, 0.01);
}
