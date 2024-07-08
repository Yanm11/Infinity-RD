#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
    time_t start_time, current_time;

    start_time = time(NULL);

    while (1)
    {
        current_time = time(NULL);
        if (difftime(current_time, start_time) >= 5.0)
        {
            break;
        }
        printf("Message at %ld seconds\n", (long)difftime(current_time,
        												  start_time));
        sleep(1);
    }

    printf("Exiting after 5 seconds\n");

    return 0;
}
