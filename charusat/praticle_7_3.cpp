#include <iostream>
using namespace std;

class Fah;

class Cel
{
private:
    float temp;

public:
    Cel(float t )
    {
        temp = t;
    }

    operator Fah();

    bool operator==(Cel c)
    {
        return temp == c.temp;
    }

    void display()
    {
        cout << temp << " C";
    }
};

class Fah
{
private:
    float temp;

public:
    Fah(float t )
    {
        temp = t;
    }

    operator Cel()
    {
        return Cel((temp - 32) * 5 / 9);
    }

    bool operator==(Fah f)
    {
        return temp == f.temp;
    }

    void display()
    {
        cout << temp << " F";
    }
};

Cel::operator Fah() // can not use direct in cel class bacause at that time fah class is not made
{
    return Fah((temp * 9 / 5) + 32);
}

int main()
{
    Cel c1(10);
    Fah f1 = c1;

    c1.display();
    cout << " = ";
    f1.display();
    cout << endl;

    Fah f2(50);
    Cel c2 = f2;

    f2.display();
    cout << " = ";
    c2.display();
    cout << endl;

    if (c1 == c2)
        cout << "Equal";
    else
        cout << "Not Equal";

    return 0;
}