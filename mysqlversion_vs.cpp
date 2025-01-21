// mysqlversion_vs.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <cstdlib>
#include <iostream>
#include <cstdio>
// loading sql library

#include <Windows.h>
#include <libloaderapi.h>
#include <processenv.h>
#include <winbase.h>
#include "mysql_connect.h"


void clearScreen()
{
#ifdef _WIN32
    std::system("cls"); // Windows
#else
    std::system("clear"); // Linux/Unix
#endif
}

void drawline(int x, char symbol)
{
    for (int i = 0; i < x; i++)
    {
        std::cout << symbol;
    }
    std::cout << std::endl;
}

void displayMenu()
{
    drawline(130, '-');
    std::cout << "\t\t\t\t\t\tWelcome to our library";
    std::cout << std::endl;
    std::cout << "\t\t\t\tSelection menu" << std::endl;
    std::cout << "1. Add new book to library" << std::endl;
    std::cout << "2. Exit" << std::endl;
    std::cout << "3. Show all books in library" << std::endl;
    std::cout << "4. Take book from library" << std::endl;
    drawline(50, '-');
    std::cout << "Choose the option: ";
}



int main()
{
    // For SQL
    MYSQL *conn = nullptr;
    MYSQL_ROW row = NULL;
    MYSQL_RES *res = nullptr;

    connection_details MySQLData;

    MySQLData.database = "books";
    MySQLData.server = "localhost";
    MySQLData.user = "root";
    MySQLData.password = NULL;


    conn = mysql_connection_setup(MySQLData);
    if (!conn)
    {
        std::cerr << "Connection to database failed. Error: " << mysql_error(conn) << "\n";
        return EXIT_FAILURE;
    }

    int commutator = 0;

    bool running = true;

    runMYSQL(conn, res, row, displayMenu, clearScreen, commutator, running);

    mysql_close(conn);
    return EXIT_SUCCESS;
}
