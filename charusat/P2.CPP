#include <iostream>

class Digital_Library
{
private: // Data Member
    std::string Book_ID, Title, auther;
    int Total_Book;

public: // Member Function
    void input();
    void Display();
    void issue();
    void returnBook();
};
void Digital_Library ::input()
{
    std::cout << "Book Name: ";
    std::cin >> Book_ID;
    std::cout << "Title of Book: ";
    std::cin >> Title;
    std::cout << "Name of auther: ";
    std::cin >> auther;
    std::cout << "Total Book: ";
    std::cin >> Total_Book;
}
void Digital_Library ::Display()
{
    std::cout << "Book Name: " << Book_ID << std::endl;
    std::cout << "Title of Book: " << Title << std::endl;
    std::cout << "Name of auther: " << auther << std::endl;
    std::cout << "Total Book: " << Total_Book << std::endl;
}
void Digital_Library ::issue()
{
    if (Total_Book > 0)
    {
        Total_Book--;
        std::cout << "\n Book issued successfully";
    }
    else
    {
        std::cout << "\n Book not available";
    }
}
void Digital_Library ::returnBook()
{
    Total_Book++;
    std::cout << "\n Book Returned successfully";
}

int main()
{
    Digital_Library B[5];

    for (int i = 0; i < 5; i++)
    {
        B[i].input();
    }
    for (int i = 0; i < 5; i++)
    {
        B[i].Display();
    }
    for (int i = 0; i < 5; i++)
    {
        B[i].issue();
    }
    for (int i = 0; i < 5; i++)
    {
        B[i].returnBook();
    }
    for (int i = 0; i < 5; i++)
    {
        B[i].Display();
    }
    return 0;
}