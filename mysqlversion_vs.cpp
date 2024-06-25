// mysqlversion_vs.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <thread>
#include <sstream>
#include <cstdio>
// loading sql library
#include <Windows.h>
// structs sql
#include "mysql_connect.h"
// functionality header
#include "Functionatlity.h"
// add class SQLibrary

#define DEBUG_MEMORY 0

#if DEBUG_MEMORY == 1 // DEBUG_MEMORY == 0 (tracking allocated memory)
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

// global variables (FOR SQL)
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

void displayMenu() {
    drawline(130, '-');
    std::cout << "\t\t\t\t\t\t\tWelcome to our library";
    std::cout << std::endl;
    std::cout << "\t\t\t\tSelection menu" << std::endl;
    std::cout << "1. Add new book to library" << std::endl;
    std::cout << "2. Exit" << std::endl;
    std::cout << "3. Show all books in library" << std::endl;
    std::cout << "4. Take book from library" << std::endl;
    drawline(50, '-');
    std::cout << "Choose the option: ";
}

void addBook() {
    int shelf_number, book_id;
    std::string book_name, author_book, datatime;

    std::cout << "Write book id: ";
    std::cin >> book_id;
    std::cout << "Write shelf_id: ";
    std::cin >> shelf_number;
    std::cin.ignore(); // Ignore remaining newline character
    std::cout << "Enter the name of the book: ";
    std::getline(std::cin, book_name);
    std::cout << "Enter the author of the book: ";
    std::getline(std::cin, author_book);
    std::cout << "Enter the datetime (YYYY-MM-DD ): ";
    std::getline(std::cin, datatime);

    char parameter_table[512];
    snprintf(parameter_table, sizeof(parameter_table),
        "INSERT INTO library VALUES (%d, %d, '%s', '%s', '%s')",
        shelf_number, book_id, book_name.c_str(), author_book.c_str(), datatime.c_str());

    if (mysql_real_query(conn, parameter_table, strlen(parameter_table)) != 0) {
        std::cerr << "INSERT INTO library failed. Error: " << mysql_error(conn) << "\n";
    }
    else {
        std::cout << "Record inserted successfully.\n";
    }
}

void showAllBooks() {
    res = mysql_execute_query(conn, "SELECT * FROM library;");
    if (!res) {
        std::cerr << "SELECT * FROM library failed. Error: " << mysql_error(conn) << "\n";
        return;
    }

    int num_fields = mysql_num_fields(res);
    while ((row = mysql_fetch_row(res))) {
        std::ostringstream oss;
        for (int i = 0; i < num_fields; i++) {
            if (i > 0) {
                oss << " | ";
            }
            oss << (row[i] ? row[i] : "NULL");
        }
        std::cout << oss.str() << std::endl;
    }
    mysql_free_result(res);
}

void takeBook() {
    int book_id;
    std::cout << "Enter the ID of the book to take: ";
    std::cin >> book_id;

    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM library WHERE book_id = %d", book_id);

    if (mysql_real_query(conn, query, strlen(query)) != 0) {
        std::cerr << "DELETE FROM library failed. Error: " << mysql_error(conn) << "\n";
    }
    else {
        std::cout << "Book with ID " << book_id << " has been taken (deleted) successfully.\n";
    }
}

int main(int argc, const char* argv[])
{
    connection_details MySQLData;
    MySQLData.database = "books";
    MySQLData.server = "localhost";
    MySQLData.user = "root";
    MySQLData.password = "";

    conn = mysql_connection_setup(MySQLData);
    if (!conn) {
        std::cerr << "Connection to database failed. Error: " << mysql_error(conn) << "\n";
        return EXIT_FAILURE;
    }

    bool running = true;
    while (running) {
        displayMenu();

        int commutator;
        std::cin >> commutator;

        switch (commutator)
        {
        case 1:
            addBook();
            break;
        case 2:
            std::cout << "Goodbye! Catch you later" << std::endl;
            running = false;
            break;
        case 3:
            showAllBooks();
            break;
        case 4:
            showAllBooks();
            takeBook();
            break;
        default:
            std::cout << "Invalid option. Please try again." << std::endl;
            break;
        }

        if (running) {
            char operator_return;
            std::cout << "Do you want to come back to the beginning (y/n): ";
            std::cin >> operator_return;

            if (operator_return == 'n') {
                std::cout << "See you next time! Goodbye" << std::endl;
                running = false;
            }
        }
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}
