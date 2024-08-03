#include <time.h> /* time_t */
#include <unistd.h> /* sleep */
#include <stdio.h>

#include "watchdog.h"

int main(int argc, char *argv[])
{
        (void)argc;
        
       if (0 !=  MMI(3,4, argv))
       {
                printf("FAILED\n");
                return -1;
       }

        sleep(30);

        DNR();

        return 0;
}