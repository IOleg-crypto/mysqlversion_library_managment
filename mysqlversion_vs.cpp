// mysqlversion_vs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>
//loading sql library

#include <Windows.h>
//structs sql
#include "mysql_connect.h"
//functionality header
#include "Functionatlity.h"
//add class SQLibrary



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
    drawline(130 , '-');
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
            std::ostringstream oss;
            for (int i = 0; i < num_fields; i++) {
                if (i > 0) {
                    oss << "|" << "\t";
                }
                oss << (row[i] ? row[i] : "NULL");
            }
            std::cout << oss.str() << std::endl;
        }
        mysql_free_result(res);
        mysql_close(conn);
       
    }


    std::cout << "Do you want come back at the beginning (y/n) :  ";
    std::cin >> operator_return;

    switch (operator_return)
    {
    case 'y':
        system("CLS");
        return main(argc, argv);
        break;
    case 'n':
        std::cout << "See you next time! Goodbye";
        exit(0);
        break;
    default:
        std::cout << "Wrong input!" << std::endl;

        while (operator_return != 'n' && operator_return != 'y')
        {
            std::cout << " You've entered an invalid response. Please only select 'n', 'y'." << std::endl;
            std::cout << "Do you want come back at the beginning (y/n) :  ";
            std::cin >> operator_return;
        }
    }
    
    

}
