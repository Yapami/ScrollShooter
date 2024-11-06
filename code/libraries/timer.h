#pragma once

#include <chrono>

class elapsed_timer
{
public:
    static elapsed_timer& get_instance()
    {
        static elapsed_timer instance;
        return instance;
    }

    void refresh_timer()
    {
        start = std::chrono::high_resolution_clock::now();
        elapsed_time = 0;
    }

    void update_timer()
    {
        std::chrono::high_resolution_clock::time_point end =
            std::chrono::high_resolution_clock::now();

        std::chrono::milliseconds duration =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        elapsed_time = duration.count();
    }

    int get_elapsed_time_milliseconds() const
    {
        return elapsed_time;
    }

    int get_elapsed_time_seconds() const
    {
        return elapsed_time / milliseconds_in_second;
    }

private:
    elapsed_timer()
    {
        refresh_timer();
    }

    elapsed_timer(const elapsed_timer&) = delete;
    elapsed_timer& operator=(const elapsed_timer&) = delete;
    elapsed_timer(elapsed_timer&&) = delete;
    elapsed_timer& operator=(elapsed_timer&&) = delete;

public:
    static constexpr float milliseconds_in_second = 1000.0;

private:
    std::chrono::high_resolution_clock::time_point start;

    int elapsed_time = 0;
};