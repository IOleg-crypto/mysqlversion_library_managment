// mysqlversion_vs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>
//loading sql library

#include <Windows.h>
//structs
#include "mysql_connect.h"
//functionality header
#include "Functionatlity.h"


using namespace std::chrono_literals;
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

    int commutator;
    char operator_return;
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
   
    connection_details MySQLData;

    //template to connect sql server
    MySQLData.database = "books";
    MySQLData.server = "localhost";
    MySQLData.user = "root";
    MySQLData.password = "";

    //first action
    drawline(133, '-');
    std::cout << "\t\t\t\t\t\t\tWelcome to our library";
    std::cout << std::endl;
    std::cout << "\t\t\t\tSelection menu" << std::endl;
    std::cout << "1 . Add new book to library" << std::endl;
    std::cout << "2 . Exit" << std::endl;
    std::cout << "3 . Show all books in library" << std::endl;
    drawline(50, '-');
    std::cout << "Choose the option : ";
    std::cin >> commutator;
  

    conn = mysql_connection_setup(MySQLData);
    res = mysql_execute_query(conn, "select * from library;");
    //initialize
    int num_fields = mysql_num_fields(res);
    switch (commutator)
    {
    case 1:
        break;
    case 2:    
        break;
    case 3:
        std::cout << "Display all information" << std::endl;
        while ((row = mysql_fetch_row(res))) {
            for (int i = 0; i < num_fields; i++) {
                std::cout << (row[i] ? row[i] : "NULL") << " ";
            }
            std::cout << std::endl;
        }
        mysql_free_result(res);
        mysql_close(conn);
        std::cout << "Do you want come back(y/n) : ";
        std::cin >> operator_return;
        while (operator_return != 'y' && operator_return != 'n')
        {
            std::cout << "Choose the correct option(y/n) : ";
            std::cin >> operator_return;
            if (operator_return == 'y')
            {
                continue;
            }
            else
            {
                return EXIT_SUCCESS;
            }
        }
    default:
        std::cout << "Choose the correct option!(1/2/3)" << std::endl;
        std::cout << std::endl;
    }

    /*
    while (commutator != 1  && commutator != 2 && commutator != 3)
    {
        std::cout << "1 . Add new book to library" << std::endl;
        std::cout << "2 . Exit" << std::endl;
        std::cout << "3 . Show all books in library" << std::endl;
        std::cout << "Choose the option :  ";
        std::cin >> commutator;
    }
    */
    std::this_thread::sleep_for(std::chrono::seconds(5));

    ;
    

}
