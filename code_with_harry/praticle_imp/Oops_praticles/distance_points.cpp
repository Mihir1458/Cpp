#include <iostream>
#include <cmath>
using namespace std;
class point
{
    int p1, p2;
    friend void dis(point d1, point d2);

public:
    point(int x, int y);
    void print()
    {
        cout << "the coordinates of the point are (" << p1 << "," << p2 << ")" << endl;
    }
};
point::point(int x, int y) // ----> This is a parameterized constructor as it takes parameters
{
    p1 = x;
    p2 = y;
}
void dis(point d1, point d2)
{
    int x1, x2, y1, y2;
    x1 = d1.p1;
    x2 = d2.p1;
    y1 = d1.p2;
    y2 = d2.p2;

    float distance_points;
    distance_points = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    cout << "the distance between the points is " << distance_points << endl;
}
int main()
{

    point d1(2, 3);
    point d2(5, 7);
    d1.print();
    d2.print();
    dis(d1, d2);
    return 0;
}