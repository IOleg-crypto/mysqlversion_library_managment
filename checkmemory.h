#ifndef CHECKMEMORY_H
#define CHECKMEMORY_H

#include <iostream> 
#include <cstdlib>  

#if DEBUG_MEMORY == 0 // DEBUG_MEMORY == 0 (tracking allocated memory)

void* operator new(size_t size) {
    std::cout << "Allocating " << size << " bytes of memory" << std::endl;
    void* ptr = malloc(size);
    if (!ptr) {
        // It's good practice to handle allocation failure
        std::cerr << "Memory allocation failed" << std::endl;
        throw std::bad_alloc(); // Standard way to handle allocation failure in C++
    }
    return ptr;
}

void operator delete(void* ptr) noexcept { // noexcept to match the standard delete signature
    if (ptr) {
        std::cout << "Freeing memory" << std::endl;
        free(ptr);
    }
}

#endif // DEBUG_MEMORY == 0

