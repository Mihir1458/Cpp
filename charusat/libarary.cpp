#include <iostream>
class digital_library
{
    std::string book_id, title, author;
    int total_copy;

public:
    void input();
    void output();
    void newbook();
    void issue();
    void returnb();
};
void digital_library::input()
{
    std::cin >> book_id;
    std::cin >> title;
    std::cin >> author;
    std::cin >> total_copy;
}
void digital_library::output()
{
    std::cout << "Book ID: " << book_id;
    std::cout << "Title: " << title;
    std::cout << "Author: " << author;
    std::cout << "Total Copies: " << total_copy;
}
void digital_library::issue()
{
    if (total_copy > 0)
    {


        total_copy--;
        std::cout << "Book issued successfully.";
    }
    else
    {
        std::cout << "No copies available.";
    }
}
void digital_library::returnb()
{
    std::cin >> book_id;
    std::cin >> title;
    std::cin >> author;
    total_copy++;
}
int main()
{
    digital_library lib[10];
    for (int i = 0; i < 10; i++)
    {
        lib[i].input();
    }
    for (int i = 0; i < 10; i++)
    {
        lib[i].output();
    }
    lib[0].issue();
    return 0;
}