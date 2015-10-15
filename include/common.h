#define TIME_CALL(ret, fun) \
    {                                                                   \
        struct timespec start_time, end_time;                           \
        long long elapse_us;                                            \
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start_time);            \
        ret = fun;                                                      \
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end_time);              \
        elapse_us = (end_time.tv_sec * 1000000 + end_time.tv_nsec/1000) \
            - (start_time.tv_sec * 1000000 + start_time.tv_nsec/1000);  \
        printf("time elapse: %lld s %lld us\n", elapse_us / 1000000,    \
                elapse_us % 1000000);                                   \
    }
