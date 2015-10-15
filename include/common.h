#define TIME_CALL(ret, fun) \
    {                                                                   \
        struct timeval start_time, end_time;                            \
        long long elapse_us;                                            \
        gettimeofday(&start_time, NULL);                                \
        ret = fun;                                                      \
        gettimeofday(&end_time, NULL);                                  \
        elapse_us = (end_time.tv_sec * 1000000 + end_time.tv_usec)      \
            - (start_time.tv_sec * 1000000 + start_time.tv_usec);       \
        printf("time elapse: %lld s %lld us\n", elapse_us / 1000000,    \
                elapse_us % 1000000);                                   \
    }
