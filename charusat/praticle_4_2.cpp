#include <iostream>
#include <cmath>
using namespace std;

class Point
{
private:
    int x, y;

public:
    Point() : x(0), y(0) {}
    Point(int x1, int y1)
    {
        x = x1;
        y = y1;
    }

    Point &move(int dx, int dy)
    {
        this->x += dx;
        this->y += dy;
        return *this;
    }

    void display()
    {
        cout << "Point: (" << x << ", " << y << ")" << endl;
    }

    double dis()
    {
        return sqrt(x * x + y * y);
    }

    void set(int newX, int newY)
    {
        x = newX;
        y = newY;
    }

    friend void reset(Point *p);
};

void update(Point *p)
{
    p->move(5, 5);
}

void reset(Point *p)
{
    p->set(0, 0);
}

int main()
{
    Point p(1, 2);

    cout << "Initial: ";
    p.display();

    p.move(2, 3).move(-1, 4).move(5, -2);

    p.display();

    update(&p);

    cout << "After update function: ";
    p.display();

    cout << "Distance: " << p.dis() << endl;

    reset(&p);

    cout << "After reset: ";
    p.display();

    return 0;
}