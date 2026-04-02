#include <iostream>
using namespace std;

template <class T1, class T2>
float funcAverage(T1 a, T2 b)
{
    float avg = (a + b) / 2.0;
    return avg;
}
template <class T>
void swapp(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

int main()
{
    float a;
    a = funcAverage(5, 2);
    printf("The average of these numbers is %f", a);
    float b = funcAverage(5, 2.8);
    printf("The average of these numbers is %f", b);
    int x = 5, y = 10;
    cout << "Before swapping: x = " << x << ", y = " << y << endl;
    swapp(x, y);
    cout << "After swapping: x = " << x << ", y = " << y << endl;

    return 0;
}
