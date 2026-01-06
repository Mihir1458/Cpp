#include <iostream>
using namespace std;
class base
{
    int d1;

public:
    int d2;
    void setd(int x, int y);
    int getd1();
    void show()
    {
        cout << "the value of the A :- " << d1 << " and B is :- " << d2 << endl;
    }
};
void base::setd(int x, int y)
{
    d1 = x;
    d2 = y;
}
int base::getd1()

{
    return d1;
}
class pro : public base
{
    int d3;

public:
    void proceess();
};
void pro ::proceess()
{
    d3 = ((d2) * (getd1()));
    cout << "The out put is :- " << d3 << endl;
}
int main()
{
    pro p1;
    p1.setd(10, 50);
    p1.show();
    p1.proceess();
}