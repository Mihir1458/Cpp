#include <iostream>
using namespace std;
class A
{
    int c;

public:
    void set(int c)
    {
        this->c = c;
    }
    void display()
    {
        cout << c;
    }
};
int main()
{
    A b;
    b.set(5);
    b.display();
    return 0;
}