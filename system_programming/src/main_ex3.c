#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main() 
{
    void *handle;
    void (*myfunction)();
    int n = 10;

    handle = dlopen("./libmylib.so", RTLD_LAZY);
    if (NULL == handle) 
    {
        printf(" dlopen error\n");
        exit(EXIT_FAILURE);
    }

    *(void **)(&myfunction) = dlsym(handle, "foo");



    myfunction(n); // Call the dynamically loaded function

    dlclose(handle);
    return 0;
}

