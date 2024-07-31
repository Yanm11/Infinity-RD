#include "imortal.h"

int main(int argc, char *argv[])
{
        time_t sleep_remain = 20;
        MMI(3,4, argv);

        while (sleep_remain)
        {
                sleep_remain = sleep(sleep_remain);
        }

        DNR();

        MMI(3,4, argv);
        sleep_remain = 20;
        while (sleep_remain)
        {
                sleep_remain = sleep(sleep_remain);
        }

        DNR();

        return 0;
}