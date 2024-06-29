#pragma once

void drawline(int x, char symbol)
{
    for (int i = 0; i < x; i++)
    {
        std::cout << symbol;
    }
    std::cout << std::endl;
}

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