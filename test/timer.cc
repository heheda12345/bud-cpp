#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <chrono>
#include <cstdio>
#include <timer.hpp>
using namespace std;
using namespace chrono;
using namespace testing;

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
        float result = result_;            \
        EXPECT_GE(result, mock);           \
        EXPECT_LT(result, mock*(1 + err)); \
    }

TEST(TimerTest, BeginEnd) {
    Timer<nanoseconds> t_nano;

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

TEST(TimerTest, StartLog) {
    Timer<microseconds> t_micro;

    for (int i = 1; i <= 5; i++) {
        t_micro.start();
        mock_sleep<microseconds>(i * 1000);
        t_micro.log();
    }
    EXPECT_EQ(t_micro.get_cnt(), 5);
    expect_near(t_micro.get_min(), 1000, 0.01);
    expect_near(t_micro.get_max(), 5000, 0.01);
    expect_near(t_micro.get_sum(), 15000, 0.01);
    expect_near(t_micro.get_avg(), 3000, 0.01);

    t_micro.clear();
    for (int i = 1; i <= 3; i++) {
        t_micro.start();
        mock_sleep<microseconds>(i * 2000);
        t_micro.log();
    }
    EXPECT_EQ(t_micro.get_cnt(), 3);
    expect_near(t_micro.get_min(), 2000, 0.01);
    expect_near(t_micro.get_max(), 6000, 0.01);
    expect_near(t_micro.get_sum(), 12000, 0.01);
    expect_near(t_micro.get_avg(), 4000, 0.01);

    std::stringstream ss;
    ss << t_micro;
    EXPECT_THAT(ss.str(),
                MatchesRegex("[0-9] iters.*, avg = [\\.0-9]+ us, min = "
                             "[\\.0-9]+ us, max = [\\.0-9]+ us"));
}