#include <iostream>
using namespace std;
class book
{
private:
    string name;
    int id;

public:
    void setdata(string n, int i)
    {
        name = n;
        id = i;
    }
    void display()
    {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
    }

};
int main()
{
    book *ptr = new book[3];
    book *tptr =ptr;
    for (int i = 0; i < 3; i++)
    {
        string name;
        int id;
        cout << "Enter name and id of book " << i + 1 << ": ";
        cin >> name >> id;
        ptr->setdata(name, id);
        ptr++;
    }
    for (int i = 0; i < 3; i++)
    {
        tptr->display();
        tptr++;
    }
    delete[] ptr;
    delete[] tptr;
    return 0;

}