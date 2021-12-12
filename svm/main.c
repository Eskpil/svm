#include "./svm.h"
#include "./inst.h"
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

int test() {
    void *object = dlopen("/usr/lib/libhello.so", RTLD_LAZY);
    void *result = dlsym(object, "hello");
    return 1;
}

int main(void) {
    printf("sizeof(Meta): %ld\n", sizeof(Meta));
    printf("Hello, World\n");
    return 0;
}

