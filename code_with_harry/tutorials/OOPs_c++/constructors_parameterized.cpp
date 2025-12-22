#include<iostream>
using namespace std;
class demo2{
    int a,b;
    public:
    demo2(int x,int y);
    void printNumber()
    {
        cout << "Your number is " << a << " + " << b << "i" << endl;
    }
};
demo2::demo2(int x,int y) // ----> This is a parameterized constructor as it takes parameters
{
    a = x;
    b = y;
    // cout<<"Hello world";
}
int main()
{
    demo2 d1(4,5);
    demo2 d2(7,8);
    d1.printNumber();
    d2.printNumber();
    return 0;
}