# include <iostream>
# include <sys/time.h>
# include <ctime>

std::size_t get_tick_count() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    return (ts.tv_sec * 1000000000 + ts.tv_nsec);
}