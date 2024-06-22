// mysqlversion_vs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//loading sql library

#include <Windows.h>

//structs
#include "mysql_connect.h"

#define DEBUG_MEMORY 0

#if DEBUG_MEMORY == 1 // DEBUG_MEMORY == 0
void* operator new(size_t size)
{
    std::cout << "Allocating " << size << " bytes of memory";
    void* ptr = malloc(size);
    return ptr;
}
void operator delete(void* ptr)
{
    std::cout << "Freeing memory";
    free(ptr);
}
#endif



int main(int argc , const char *argv[])
{
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    //conn = mysql_init(NULL);
    std::cout << "Working debug" << std::endl;

}
