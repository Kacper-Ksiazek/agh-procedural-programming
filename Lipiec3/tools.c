#include "stdio.h"
#include "stdlib.h"

#include "tools.h"

void ensureProperMemoryAllocation(void *p) {
    if(p == NULL){
        fprintf(stderr,"Memory could not have been allocated!");
        exit(1);
    }
}
