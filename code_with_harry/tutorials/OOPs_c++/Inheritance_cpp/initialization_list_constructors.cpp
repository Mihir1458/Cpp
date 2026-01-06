#include<iostream>
using namespace std;
/*
Syntax for initialization list in constructor:
constructor (argument-list) : initilization-section
{
    assignment + other code;
}
    */
class Test
{
    int a;
    int b;

public:
    //Test(int i, int j) : a(i), b(j+i)
    //Test(int i, int j) : a(i), b(j*i)
    Test(int i, int j) : a(b*j), b(i)
    //Test(int i, int j) :  b(a*i), a(i) // Note: a is initialized after b because of order of declaration
   // Test(int i, int j) : b(i), a(j)
    {
        cout << "Constructor executed"<<endl;
        cout << "Value of a is "<<a<<endl;
        cout << "Value of b is "<<b<<endl;
    }
};

int main()
{
    Test t(4, 6);

    return 0;
}
