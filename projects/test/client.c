#include <time.h> /* time_t */
#include <unistd.h> /* sleep */
#include <stdio.h>

#include "watchdog.h"

int main(int argc, char *argv[])
{
        time_t sleep_remain = 20;

        (void)argc;
        
       if (0 !=  MMI(3,4, argv))
       {
                printf("FAILED\n");
                return -1;
       }

        while (sleep_remain)
        {
                sleep_remain = sleep(sleep_remain);
        }

        DNR();

        if (0 !=  MMI(3,4, argv))
       {
                printf("FAILED\n");
                return -1;
       }
        sleep_remain = 20;
        while (sleep_remain)
        {
                sleep_remain = sleep(sleep_remain);
        }

        DNR();

        return 0;
}