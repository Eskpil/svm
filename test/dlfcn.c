#include <stdio.h>
#include <dlfcn.h>

int main(void) {
    
    void *object = dlopen("/usr/lib/libhello.so", RTLD_LAZY);
    void (*result)() = dlsym(object, "hello");
    result();
    dlclose(object);

    return 0;
}
