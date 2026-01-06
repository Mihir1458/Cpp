#include <iostream>
using namespace std;
class b
{
    int a, b1;

public:
    b();      // default constructor declaration
    b(int x); // parameterized constructor
    b(int x, int y);
    void printNumber()
    {
        cout << "Your number is " << a << " + " << b1 << "i" << endl;
    }
};
b::b()
{
    a = 9;
    b1 = 9;
}
b::b(int x)
{
    a = x;
    b1 = 9;
}
b::b(int x, int y)
{
    a = x;
    b1 = y;
}
int main()
{
    b obj1;
    b obj2(5);
    b obj3(5, 6);
    obj1.printNumber();
    obj2.printNumber();
    obj3.printNumber();
}