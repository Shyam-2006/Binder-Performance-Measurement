#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
int main()
{
    struct timespec start, end;
    int fd = open("/dev/binder", O_RDWR);
    if(fd < 0)
    {
        perror("open");
        return 1;
    }
    clock_gettime(CLOCK_MONOTONIC, &start);

    for(int i=0;i<10000;i++)
    {
        close(fd);

        fd = open("/dev/binder", O_RDWR);

        if(fd < 0)
        {
            perror("open");
            return 1;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    long long elapsed_ns =
        (end.tv_sec - start.tv_sec) * 1000000000LL +
        (end.tv_nsec - start.tv_nsec);

    printf("Total Time = %lld ns\n", elapsed_ns);

    printf("Average Open Latency = %.2f ns\n",
           (double)elapsed_ns / 10000);
    close(fd);
    return 0;
}
