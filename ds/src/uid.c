/********************************** 
   Code by: Yan Meiri	
   Project: UID
   Date: 28/05/24
   Review by: amit
   Review Date: 29/05/2024
   Approved by: amit
   Approval Date: 29/05/204
**********************************/

#include <time.h> /* time */
#include <unistd.h> /* getpid */
#include <pthread.h> /* PTHREAD_MUTEX_INITIALIZER  pthread_mutex_lock*/

#include "uid.h" 

static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER; 
const ilrd_uid_t BadUID = {0};


ilrd_uid_t UIDCreate(void)
{
	ilrd_uid_t UID = {0};
	static size_t counter = 1;
	

    
	UID.timestamp = time(NULL);
	if ((time_t)-1 == UID.timestamp)
	{
		 /* unlocking the mutex */
		pthread_mutex_unlock(&g_lock);
		
		return BadUID;
	}
	
	/* locking the mutex */
    if (0 != pthread_mutex_lock(&g_lock))
    {
    	return BadUID;
    }
    
	UID.counter = counter;	
	++counter;
	
	/* unlocking the mutex */
    if (0 != pthread_mutex_unlock(&g_lock))
    {
    	return BadUID;
    }
    
	UID.pid = getpid();

	return UID;
}

int IsSameUID(const ilrd_uid_t uid1, const ilrd_uid_t uid2)
{
	return ((uid1.timestamp == uid2.timestamp) &&
			(uid1.counter == uid2.counter) &&
			(uid1.pid == uid2.pid));
}
