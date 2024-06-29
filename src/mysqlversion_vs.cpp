// mysqlversion_vs.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <thread>
#include <sstream>
#include <cstdio>
#include <iomanip>
// loading sql library
#include <Windows.h>
// structs sql
#include "mysql_connect.h"
// functionality header
#include "Functionatlity.h"
// add class SQLibrary

#define DEBUG_MEMORY 1

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

// global variables (FOR SQL)
MYSQL *conn;
MYSQL_ROW row;
MYSQL_RES *res;

void addBook(MYSQL *conn)
{
    int shelf_number, book_id;
    std::string book_name, author_book, datatime;

    std::cout << "Write book id: ";
    std::cin >> book_id;
    std::cout << "Write shelf_number: ";
    std::cin >> shelf_number;
    std::cin.ignore(); // Ignore remaining newline character
    std::cout << "Enter the name of the book: ";
    std::getline(std::cin, book_name);
    std::cout << "Enter the author of the book: ";
    std::getline(std::cin, author_book);
    std::cout << "Enter the datetime (YYYY-MM-DD): ";
    std::getline(std::cin, datatime);

    // Check if the book_id already exists in the table
    char check_query[256];
    snprintf(check_query, sizeof(check_query), "SELECT * FROM library WHERE name_id = %d", book_id);

    if (mysql_real_query(conn, check_query, strlen(check_query)) != 0)
    {
        std::cerr << "Check book_id failed. Error: " << mysql_error(conn) << "\n";
        return;
    }

    MYSQL_RES *check_res = mysql_store_result(conn);
    if (!check_res)
    {
        std::cerr << "Check book_id result failed. Error: " << mysql_error(conn) << "\n";
        return;
    }

    MYSQL_ROW check_row = mysql_fetch_row(check_res);
    int count = atoi(check_row[0]);
    mysql_free_result(check_res);

    if (count > 0)
    {
        std::cout << "Book with ID " << book_id << " already exists. Please use a different ID.\n";
        return;
    }

    // Proceed with insertion if the book_id does not exist
    char parameter_table[512];
    snprintf(parameter_table, sizeof(parameter_table),
             "INSERT INTO library (shelf_number, book_id, book_name, author_book, datetime) VALUES (%d, %d, '%s', '%s', '%s')",
             shelf_number, book_id, book_name.c_str(), author_book.c_str(), datatime.c_str());

    if (mysql_real_query(conn, parameter_table, strlen(parameter_table)) != 0)
    {
        std::cerr << "INSERT INTO library failed. Error: " << mysql_error(conn) << "\n";
    }
    else
    {
        std::cout << "Record inserted successfully.\n";
    }
}

void showAllBooks(MYSQL_RES *res)
{
    res = mysql_execute_query(conn, "SELECT * FROM library;");
    if (!res)
    {
        std::cerr << "SELECT * FROM library failed. Error: " << mysql_error(conn) << "\n";
        return;
    }

    int num_fields = mysql_num_fields(res);

    // Print table header
    std::cout << std::left << std::setw(15) << "Shelf Number"
              << std::left << std::setw(10) << "Book ID"
              << std::left << std::setw(30) << "Book Name"
              << std::left << std::setw(30) << "Author Book"
              << std::left << std::setw(20) << "Datetime" << std::endl;
    drawline(105, '-'); // Adjust this according to the total width of the table

    // Print table rows
    while ((row = mysql_fetch_row(res)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            if (i == 0)
                std::cout << std::left << std::setw(15) << (row[i] ? row[i] : "NULL");
            else if (i == 1)
                std::cout << std::left << std::setw(10) << (row[i] ? row[i] : "NULL");
            else if (i == 2)
                std::cout << std::left << std::setw(30) << (row[i] ? row[i] : "NULL");
            else if (i == 3)
                std::cout << std::left << std::setw(30) << (row[i] ? row[i] : "NULL");
            else if (i == 4)
                std::cout << std::left << std::setw(20) << (row[i] ? row[i] : "NULL");
        }
        std::cout << std::endl;
    }
    mysql_free_result(res);
    drawline(105, '-'); // Adjust this according to the total width of the table
}

void takeBook(MYSQL *conn)
{
    int book_id;
    std::cout << "Enter the ID of the book to take: ";
    std::cin >> book_id;

    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM library WHERE name_id = %d", book_id);

    if (mysql_real_query(conn, query, strlen(query)) != 0)
    {
        std::cerr << "DELETE FROM library failed. Error: " << mysql_error(conn) << "\n";
    }
    else
    {
        std::cout << "Book with ID " << book_id << " has been taken (deleted) successfully.\n";
    }
}

int main(int argc, const char *argv[])
{
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
            break;
        case 3:
            showAllBooks(res);
            break;
        case 4:
            showAllBooks(res);
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
