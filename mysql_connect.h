#pragma once
#include <mysql.h>

struct connection_details
{
    const char* server;
    const char* user;
    const char* password;
    const char* database;
};

MYSQL* mysql_connection_setup(connection_details mylibrary_details)
{
    MYSQL* connection = mysql_init(NULL);
    if (!mysql_real_connect(connection , mylibrary_details.server , mylibrary_details.user , mylibrary_details.password , mylibrary_details.database , 0 , NULL , 0 ))
    {
        std::cout << "Connection failed " << mysql_error << std::endl;
    }
};