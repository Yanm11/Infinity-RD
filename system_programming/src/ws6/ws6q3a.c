#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#include "ws6_ex1.h"

int main(void)
{
	void *handle;
    void (*myfunction)();
    

    handle = dlopen("./libq3a.so", RTLD_LAZY );
    if (NULL == handle) 
    {
        printf(" dlopen error\n");
        return -1;
    }

    *(void **)(&myfunction) = dlsym(handle, "PrintGlobalVariableAddress");

	printf("global x address is at: %p\n", &x);
	
    myfunction();
    
    dlclose(handle);

    return 0;	
}


