#include "./svm.h"
#include "./inst.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) {

    Svm svm = {0};

    svm_execute_program(&svm, 500);
    
    return 0;
}

