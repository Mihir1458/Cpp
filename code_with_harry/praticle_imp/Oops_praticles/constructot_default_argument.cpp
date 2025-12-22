#include <iostream>
using namespace std;
class pp
{
    int a, b, c;

public:
    pp(int x, int y = 15, int z = 78)
    {
        a = x;
        b = y;
        c = z;
    }
    void printNumber()
    {
        cout << "The value of a, b and c is " << a << ", " << b << " and " << c << endl;
    }
};
int main()
{
    pp l1(25);
    pp l2(25, 66);
    pp l3(25, 30, 40);

    l1.printNumber();
    l2.printNumber();
    l3.printNumber();
    return 0;
}
