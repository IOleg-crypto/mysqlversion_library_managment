#pragma once

void drawline(int x, char symbol)
{
    for (int i = 0; i < x; i++)
    {
        std::cout << symbol;
    }
    std::cout << std::endl;
}

class SQLLibrary
{
public:
    void addBook() {}
    void addAuthor() {}
    void addShelf() {}
    void getAuthor() {}
    void getShelf() {}
    void getBook() {}
    void PrintBook() {}
};
