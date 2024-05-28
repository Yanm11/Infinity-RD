#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#include "memory_mapping.h"

int main(int argc, char *argv[], char *envp[])
{
    char** p_command_line_arguments = argv;
    char** p_environment_variables = envp;
    void *handle;
    void (*myfunction)();

    MemoryMappingCode1(1,1.0f,1.0);

    /* Cancel "unsused variable" warnings: */
    (void)p_environment_variables;
    (void)p_command_line_arguments;
    (void)argc;    

    handle = dlopen("./libfoo1.so", RTLD_LAZY );
    if (NULL == handle) 
    {
        printf(" dlopen error\n");
        return -1;
    }

    *(void **)(&myfunction) = dlsym(handle, "Foo");


    myfunction(1,1.0f,1.0);
    Foo2(1,1.0f,1.0);
    
    dlclose(handle);
    return 0;
}
