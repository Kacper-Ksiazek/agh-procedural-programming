#include "stdio.h"
#include "stdlib.h"

#include "tools.h"

void checkPointer(void *p, char *msgOnError) {
    if (p == NULL) {
        fprintf(stderr, "%s", msgOnError);
        exit(1);
    }
}