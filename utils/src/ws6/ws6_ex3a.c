#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#include "ws6_ex1.h"


int main(void)
{
	void *handle;
    void (*myfunction)();
	
	PrintGlobalVariableAddress();

    handle = dlopen("./libws6foo1.so", RTLD_LAZY );
    if (NULL == handle) 
    {
        printf(" dlopen error\n");
        return -1;
    }

    *(void **)(&myfunction) = dlsym(handle, "Foo");


    myfunction();
    dlclose(handle);
 
    handle = dlopen("./libws6foo2.so", RTLD_LAZY );
    if (NULL == handle) 
    {
        printf(" dlopen error2\n");
        return -1;
    }

    *(void **)(&myfunction) = dlsym(handle, "Foo2");

    myfunction();
    dlclose(handle);
    
    return 0;
	
	
	
}
