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

    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (!stmt)
    {
        std::cerr << "mysql_stmt_init() failed. Error: " << mysql_error(conn) << "\n";
        return;
    }

    const char *query = "INSERT INTO library (shelf_number, book_name, author_name_book, TimeAddBook) VALUES (?, ?, ?, ?)";
    if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0)
    {
        std::cerr << "mysql_stmt_prepare() failed. Error: " << mysql_stmt_error(stmt) << "\n";
        mysql_stmt_close(stmt);
        return;
    }

    MYSQL_BIND bind[4];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = &shelf_number;

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (void *)(book_name.c_str());
    bind[1].buffer_length = book_name.size();

    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (void *)author_name_book.c_str();
    bind[2].buffer_length = author_name_book.size();

    bind[3].buffer_type = MYSQL_TYPE_STRING;
    bind[3].buffer = (void *)datetime.c_str();
    bind[3].buffer_length = datetime.size();

    if (mysql_stmt_bind_param(stmt, bind) != 0)
    {
        std::cerr << "mysql_stmt_bind_param() failed. Error: " << mysql_stmt_error(stmt) << "\n";
        mysql_stmt_close(stmt);
        return;
    }

    if (mysql_stmt_execute(stmt) != 0)
    {
        std::cerr << "INSERT INTO library failed. Error: " << mysql_stmt_error(stmt) << "\n";
    }
    else
    {
        std::cout << "Record inserted successfully.\n";
    }

    mysql_stmt_close(stmt);
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
    snprintf(query, sizeof(query), "DELETE FROM library WHERE name_id = %d", book_id); // Assuming the primary key column is 'id'

    if (mysql_real_query(conn, query, strlen(query)) != 0)
    {
        std::cerr << "DELETE FROM library failed. Error: " << mysql_error(conn) << "\n";
    }
    else
    {
        std::cout << "Book with ID " << book_id << " has been taken (deleted) successfully.\n";
    }
}

void runMYSQL(MYSQL* conn, MYSQL_RES* res, MYSQL_ROW row , void (*DisplayMenu)() , void (*clearScreen)() , int commutator , bool IsRunning)
{

    while (IsRunning)
    {
        DisplayMenu();

        std::cin >> commutator;

        switch (commutator)
        {
        case 1:
            addBook(conn);
            break;
        case 2:
            std::cout << "Goodbye! Catch you later" << std::endl;
            IsRunning = false;
            clearScreen();
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

        if (IsRunning)
        {
            char operator_return;
            std::cout << "Do you want to come back to the beginning (y/n): ";
            std::cin >> operator_return;
            clearScreen();

            if (operator_return == 'n')
            {
                std::cout << "See you next time! Goodbye" << std::endl;
                IsRunning = false;
            }
        }
    }
}
