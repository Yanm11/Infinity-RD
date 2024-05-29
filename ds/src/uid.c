/********************************** 
   Code by: Yan Meiri	
   Project: UID
   Date: 28/05/24
   Review by: amit
   Review Date: 29/05/2024
   Approved by: 
   Approval Date: 
**********************************/

#include <time.h> /* time */
#include <unistd.h> /* getpid */

#include "uid.h" 

const ilrd_uid_t BadUID = {0};


ilrd_uid_t UIDCreate(void)
{
	ilrd_uid_t UID = {0};
	static size_t counter = 1;
	
	UID.timestamp = time(NULL);
	UID.counter = counter;
	UID.pid = getpid();
	
	++counter;
	
	return UID;
}

int IsSameUID(const ilrd_uid_t uid1, const ilrd_uid_t uid2)
{
	return ((uid1.timestamp == uid2.timestamp) &&
			(uid1.counter == uid2.counter) &&
			(uid1.pid == uid2.pid));
}
