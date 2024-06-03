/********************************** 
   Code by: Yan Meiri	
   Project: fixed size allocator
   Date: 2/06/24
   Review by: or
   Review Date: 03/06/24
   Approved by: or
   Approval Date: 03/06/24
**********************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "task.h"
#include "uid.h" 

struct task
{
    ilrd_uid_t uid;
    time_t exe_time;
    time_t interval_in_seconds;
    void (*action)(void *params);
    void *params;
};




