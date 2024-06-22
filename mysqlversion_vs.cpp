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
   
    connection_details MySQLData;

    MySQLData.database = "books";
    MySQLData.server = "localhost";

    MySQLData.user = "root";
    MySQLData.password = "";

    conn = mysql_connection_setup(&MySQLData);
    res = mysql_execute_query(conn, "select * from books.library;");

    std::cout << "Display all information" << std::endl;

    while ((row = mysql_fetch_row(res)) != NULL)
    {
        std::cout << row[0] << "|" << row[1] << "|" << row[2] << "|" << row[3] << std::endl;

        std::cout << std::endl;
    }

    mysql_free_result(res);
    mysql_close(conn);

    

}
