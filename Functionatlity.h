#pragma once

void drawline(int x, char symbol)
{
    for (int i = 0; i < x; i++)
    {
        std::cout << symbol;
    }
    std::cout << std::endl;
}

void addInformationBook(int shelf_number , int book_id , std::string book_name , std::string author_book , std::string datatime , MYSQL *conn) 
{
    // Construct the INSERT query with parameters
    char query[512];
    sprintf_s(query, "INSERT INTO library (int_column1, int_column2, str_column1, str_column2, str_column3) VALUES (%d, %d, %s, '%s', '%s')",
        shelf_number, book_id, book_name.c_str(), author_book.c_str(), datatime.c_str());

    if (mysql_query(conn, "SELECT * FROM library")) {
        std::cerr << "SELECT * FROM your_table failed. Error: " << mysql_error(conn) << "\n";
        mysql_close(conn);
    }
    if (mysql_query(conn, "SELECT int_column1, int_column2, str_column1, str_column2, str_column3 FROM library")) {
        std::cerr << "SELECT * FROM library failed. Error: " << mysql_error(conn) << "\n";
        mysql_close(conn);
    }
}
