#include <iostream>
using namespace std;
class complex
{
    int a;
    int b;

public:
    void getnum(int a1, int b1)
    {
        a = a1;
        b = b1;
    }
    void setcom(complex o1, complex o2)
    {
        a = o1.a + o2.a;
        b = o1.b + o2.b;
    }

    void print()
    {
        cout << "Your complex numbers id :- " << a << "+" << b << "i" << endl;
    }
};
int main()
{
    complex a, b, c;
    a.getnum(1, 2);
    a.print();
    b.getnum(3, 4);
    b.print();

    c.setcom(a, b);
    c.print();
    return 0;
}