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

#define DEBUG_MEMORY 0


typedef void (*AddFunctionPtr)();
  // Define a function pointer type for the function you want to load

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



int main(int argc, const char *argv[])
{
    // For SQL
    MYSQL *conn = nullptr;
    MYSQL_ROW row = NULL;
    MYSQL_RES *res = nullptr;

    connection_details MySQLData;

    MySQLData.database = "books";
    MySQLData.server = "localhost";
    MySQLData.user = "root";
    MySQLData.password = "";

    

    conn = mysql_connection_setup(MySQLData);
    if (!conn)
    {
        std::cerr << "Connection to database failed. Error: " << mysql_error(conn) << "\n";
        return EXIT_FAILURE;
    }

    bool running = true;
    while (running)
    {
        displayMenu();

        int commutator;
        std::cin >> commutator;

        switch (commutator)
        {
        case 1:
            addBook(conn);
            break;
        case 2:
            std::cout << "Goodbye! Catch you later" << std::endl;
            running = false;
            system("cls");
            break;
        case 3:
            showAllBooks(res, conn, row);
            break;
        case 4:
            showAllBooks(res, conn, row);
            takeBook(conn);
            break;
        default:
            std::cout << "Invalid option. Please try again." << std::endl;
            break;
        }

        if (running)
        {
            char operator_return;
            std::cout << "Do you want to come back to the beginning (y/n): ";
            std::cin >> operator_return;
            system("cls");

            if (operator_return == 'n')
            {
                std::cout << "See you next time! Goodbye" << std::endl;
                running = false;
            }
        }
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}
