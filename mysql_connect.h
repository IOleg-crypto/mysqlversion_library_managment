#ifndef MYSQL_CONNECT_H
#define MYSQL_CONNECT_H

#ifdef _WIN32
    #pragma once
#endif

#include <mysql.h>
#include <limits.h>

struct connection_details {
    const char *server;
    const char *user;
    const char *password;
    const char *database;
};


MYSQL *mysql_connection_setup(const connection_details &mylibrary_details);
MYSQL_RES *mysql_execute_query(MYSQL *connection, const char *sql_query);
void addBook(MYSQL *conn);
void showAllBooks(MYSQL_RES *res, MYSQL *conn, MYSQL_ROW row);
void takeBook(MYSQL *conn);
void drawline(int x, char symbol);

#endif // MYSQL_CONNECT_H
