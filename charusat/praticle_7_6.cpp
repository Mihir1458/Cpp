
#include <iostream>
using namespace std;

class Base
{
public:
    Base()
    {
        cout << "Base Constructor" << endl;
    }

    virtual ~Base()
    {
        cout << "Base Destructor" << endl;
    }
};

class Derived : public Base
{
    int *A;

public:
    Derived()
    {
        A = new int(20);
        cout << "Derived Constructor" << endl;
    }

    ~Derived()
    {
        delete A;
        cout << "Derived Destructor" << endl;
    }
};

int main()
{

    Base *ptr2 = new Derived();
    delete ptr2;

    return 0;
}