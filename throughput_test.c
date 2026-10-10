#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define ITERATIONS 100000

int main()
{
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for(int i = 0; i < ITERATIONS; i++)
    {
        int fd = open("/dev/binder", O_RDWR);

        if(fd >= 0)
            close(fd);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    long long elapsed_ns =
        (end.tv_sec - start.tv_sec) * 1000000000LL +
        (end.tv_nsec - start.tv_nsec);

    double seconds = elapsed_ns / 1e9;

    double throughput = ITERATIONS / seconds;

    printf("Elapsed Time = %.6f sec\n", seconds);
    printf("Throughput = %.2f ops/sec\n", throughput);

    return 0;
}
