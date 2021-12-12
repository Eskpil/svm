#include <stdio.h>
#include <string.h>

char *source_code = 
   "push 1\n"
   "push 1\n"
   "add\n"
   "push 2\n"
   "sub\n";


void tokenize(char *source, size_t size) {
    while (size > 0) {
        char *end = memchr(source, '\n', size);
        size_t n = end != NULL ? (size_t) (end - source) : size;

        printf("#%.*s#\n", (int) n, source);
    
        source = end;
        size -= n;

        if (source != NULL) {
            source += 1;
            size -= 1;
        }
    } 
}


int main(void) {
    tokenize(source_code, strlen(source_code));
    return 0;
}
