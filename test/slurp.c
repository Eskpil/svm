#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    assert(argc >= 2 && "Not enough arguments");
    const char *filepath = argv[1];

    int fd = open(filepath, O_RDWR);

    struct stat statbuf;
    int err = fstat(fd, &statbuf);

    assert(err >= 0);

    char *ptr = (char*) mmap(NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    close(fd);

    printf("file contains:\n%s\n", ptr);

    munmap(ptr, statbuf.st_size);
}
