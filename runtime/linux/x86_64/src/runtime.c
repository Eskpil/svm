#include "types.h"
#include "syscalls.h"

// #define O_RDWR 00000200
#define O_RDWR 0x2
#define O_CREAT 00000100
#define M_READ 00400
#define M_WRITE 00200

void _start() {
    const char *message = "Hello, World\n";
    const char *file = "linus";
    // int fd = open(file, 0x2 | 00000100, 00200 | 00400);
    int fd = open(file, O_RDWR | O_CREAT, M_READ | M_WRITE);

    write(fd, message, 13);    

    close(fd);

    write(1, message, 13);

    exit(0);
}
