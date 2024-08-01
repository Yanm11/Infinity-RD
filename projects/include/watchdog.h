#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

#include <stddef.h> /* size_t */

/*
MMI(MakeMeImortal)
description: will activaate a watchdog process that will execute the client 
            program again once it has been killed until DNR will be called
input: interval in second, times of reptitions to send a signal before revivng, and all arguments nececary to execute
return: status 0 for success non 0 otherwise
time comlexity: O(1)
space complexity: O(1)
*/
int MMI(size_t interval_in_seconds, size_t repetitions, char **argv);

/*
MMI(MakeMeImortal)
description: stop the watchdog from running
input: nothing
return: nothing
time comlexity: O(1)
space complexity: O(1)
*/
void DNR(void);

#endif /*__WATCHDOG_H__ */