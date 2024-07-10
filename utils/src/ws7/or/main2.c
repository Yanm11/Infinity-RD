#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

void Foo(void);

int main() 
{

    void *handle1 = dlopen("./libfoo.so", RTLD_LAZY);
    if (!handle1) 
    {
        fprintf(stderr, "Failed to load libfoo.so: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }


    void (*Foo)() = dlsym(handle1, "Foo");
    char *error = dlerror();
    if (error != NULL) 
    {
        fprintf(stderr, "Failed to find Foo: %s\n", error);
        dlclose(handle1);
        exit(EXIT_FAILURE);
    }


    Foo();

    dlclose(handle1);
    
    sleep(100);
    return 0;
}
