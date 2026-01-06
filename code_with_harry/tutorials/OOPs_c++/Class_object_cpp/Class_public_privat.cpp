#include <iostream>
using namespace std;
void getset(int a1, int b1);
void getcall();
class bank
{
private:
    int a, b;

public:
    int c, d, e;
    void getset(int a, int b);
    void getcall()
    {
        cout << "The value of a is: " << a << endl;
        cout << "The value of b is: " << b << endl;
        cout << "The value of c is: " << c << endl;
        cout << "The value of d is: " << d << endl;
        cout << "The value of e is: " << e << endl;
    }
};
void bank ::getset(int a1, int b1)
{
    a = a1;
    b = b1;
}
int main()
{ // b.a=78 {this will genrate the error beacuse it private canot be accsesed}
    bank b;
    b.c = 59;
    b.d = 5;
    b.e = 8;
    b.getset(10, 20);
    b.getcall();
    return 0;
}
