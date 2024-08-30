#pragma once

#include "mysqlversion_vs.cpp"

#if DEBUG_MEMORY == 0 // DEBUG_MEMORY == 0 (tracking allocated memory)
void *operator new(size_t size)
{
    std::cout << "Allocating " << size << " bytes of memory";
    void *ptr = malloc(size);
    return ptr;
}
void operator delete(void *ptr)
{
    std::cout << "Freeing memory";
    free(ptr);
}
#endif
