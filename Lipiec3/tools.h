#pragma once

/**
 * @param p pointer; result of either **calloc** or **malloc**
 * @throw Error when memory has not been allocated properly
 */
void ensureProperMemoryAllocation(void *p);