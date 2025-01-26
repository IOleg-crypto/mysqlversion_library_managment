// mysqlversion_vs.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "mysql_connect.h"

#include <iostream>
#include <memory>

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
#ifdef DEBUG_TIME
    auto start = std::chrono::high_resolution_clock::now();
#endif
    MYSQL *conn = nullptr;
    MYSQL_ROW row = NULL;
    MYSQL_RES *res = nullptr;

    int choice = 0;

    bool running = true;

    connection_details MySQLData {"localhost" , "root" , NULL , "books"};

    conn = mysql_connection_setup(MySQLData);
    if (!conn)
    {
        std::cerr << "Connection to database failed. Error: " << mysql_error(conn) << "\n";
        return EXIT_FAILURE;
    }
    runMYSQL(conn, res, row, displayMenu, clearScreen, choice, running);
#ifdef DEBUG_TIME
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Duration: " << duration.count() << "ms" << std::endl;
#endif
    mysql_close(conn);
    return EXIT_SUCCESS;
}
