/********************************** 
   Code by: Yan Meiri	
   Project: UID
   Date: 2805/24
   Review by: 
   Review Date: 
   Approved by: 
   Approval Date: 
**********************************/

#include <time.h> /* time */
#include <unistd.h> /* sleep */

#include "uid.h" 

const ilrd_uid_t BadUID = {0};


ilrd_uid_t UIDCreate(void)
{
	ilrd_uid_t UID = {0};
	static size_t counter = 1;
	
	UID.timestamp = time(NULL);
	
	sleep(1);
	
	UID.counter = counter;
	UID.pid = getpid() ^ counter;
	
	++counter;
	
	return UID;
}

int IsSameUID(const ilrd_uid_t uid1, const ilrd_uid_t uid2)
{
	if ((uid1.timestamp == uid2.timestamp) &&
		(uid1.counter == uid2.counter) &&
		(uid1.pid == uid2.pid))
	{
		return 1;
	}
	
	return 0;
}
