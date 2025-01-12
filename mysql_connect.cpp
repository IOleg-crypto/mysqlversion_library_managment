#include "mysql_connect.h" // add header file

#include <string>
#include <iostream>
#include <cstdio>
#include <string>
#include <Windows.h>
#include <libloaderapi.h>
#include <iomanip>

MYSQL* mysql_connection_setup(const connection_details &mylibrary_details)
{
    MYSQL* connection = mysql_init(NULL);
    if (!mysql_real_connect(connection , mylibrary_details.server , mylibrary_details.user , mylibrary_details.password , mylibrary_details.database , 0 , NULL , 0 ))
    {
        std::cout << "Connection failed " << mysql_error(connection) << std::endl;
        mysql_close(connection);
    }
    return connection;
};

MYSQL_RES* mysql_execute_query(MYSQL *connection , const char *sql_query)
{
    if (mysql_query(connection, sql_query))
    {
        std::cout << "MYSQL query error " << mysql_error(connection) << std::endl;
        mysql_close(connection);
    }
    return mysql_use_result(connection);
}

void addBook(MYSQL *conn)
{
    int shelf_number;
    std::string book_name, author_name_book, datetime;

    std::cout << "Write shelf_number: ";
    std::cin >> shelf_number;

    std::cout << "Enter the name of the book: ";
    std::cin >> std::ws >> book_name;

    std::cout << "Enter the author of the book: ";
    std::cin >> std::ws >> author_name_book;
 
    std::cout << "Enter the datetime (YYYY-MM-DD): ";
    std::cin >> std::ws >> datetime;

    // Check if the book_id already exists in the table
    char check_query[256];
    snprintf(check_query, sizeof(check_query), "SELECT * FROM library WHERE book_name = '%s'", book_name.c_str());

    if (mysql_real_query(conn, check_query, strlen(check_query)) != 0)
    {
        std::cerr << "Check book_name failed. Error: " << mysql_error(conn) << "\n";
        return;
    }

    MYSQL_RES *check_res = mysql_store_result(conn);
    if (!check_res)
    {
        std::cerr << "Check book_name result failed. Error: " << mysql_error(conn) << "\n";
        return;
    }

    MYSQL_ROW check_row = mysql_fetch_row(check_res);
    if (check_row) // If a row exists, then the book already exists
    {
        std::cout << "Book with the name \"" << book_name << "\" already exists. Please use a different name.\n";
        mysql_free_result(check_res);
        return;
    }
    mysql_free_result(check_res);

    // Proceed with insertion if the book_name does not exist
    char parameter_table[512];
    snprintf(parameter_table, sizeof(parameter_table),
             "INSERT INTO library (shelf_number, book_name, author_name_book, TimeAddBook) VALUES (%d, '%s', '%s', '%s')",
             shelf_number, book_name.c_str(), author_name_book.c_str(), datetime.c_str());

    if (mysql_real_query(conn, parameter_table, strlen(parameter_table)) != 0)
    {
        std::cerr << "INSERT INTO library failed. Error: " << mysql_error(conn) << "\n";
        std::exit(1);
    }
    else
    {
        std::cout << "Record inserted successfully.\n";
    }
}

void showAllBooks(MYSQL_RES *res, MYSQL *conn, MYSQL_ROW row)
{
    res = mysql_execute_query(conn, "SELECT * FROM library;");
    if (!res)
    {
        std::cerr << "SELECT * FROM library failed. Error: " << mysql_error(conn) << "\n";
        return;
    }

    int num_fields = mysql_num_fields(res);

    // Print table header
    std::cout << std::left << std::setw(15) << "ID book"
              << std::left << std::setw(15) << "Shelf Number"
              << std::left << std::setw(15) << "Book Name"
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
                std::cout << std::left << std::setw(30) << (row[i] ? row[i] : "NULL");
            else if (i == 2)
                std::cout << std::left << std::setw(40) << (row[i] ? row[i] : "NULL");
            else if (i == 3)
                std::cout << std::left << std::setw(20) << (row[i] ? row[i] : "NULL");
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
    snprintf(query, sizeof(query), "DELETE FROM library WHERE id = %d", book_id); // Assuming the primary key column is 'id'

    if (mysql_real_query(conn, query, strlen(query)) != 0)
    {
        std::cerr << "DELETE FROM library failed. Error: " << mysql_error(conn) << "\n";
    }
    else
    {
        std::cout << "Book with ID " << book_id << " has been taken (deleted) successfully.\n";
    }
}
