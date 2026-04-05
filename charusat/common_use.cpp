#include<iostream>
#include<cmath>
using namespace std;

class Point {
private:
    int x, y;

public:
    // Constructor
    Point(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
    }

    // Chainable move function
    Point& move(int dx, int dy) {
        this->x += dx;
        this->y += dy;
        return *this;  // key for chaining
    }

    // Display
    void display() {
        cout << "Point: (" << x << ", " << y << ")" << endl;
    }

    // Distance from origin
    double distanceFromOrigin() {
        return sqrt(x*x + y*y);
    }

    // Set absolute coordinates
    void set(int newX, int newY) {
        x = newX;
        y = newY;
    }

    // Friend function (optional access)
    friend void resetPoint(Point* p);
};

// Pass-by-reference using pointer
void updatePoint(Point* p) {
    p->move(5, 5); // modifies original object
}

// Reset function
void resetPoint(Point* p) {
    p->set(0, 0);
}

int main() {
    Point p(1, 2);

    cout << "Initial: ";
    p.display();

    // 🔹 Chaining (at least 3 moves)
    p.move(2, 3).move(-1, 4).move(5, -2);

    cout << "After chaining: ";
    p.display();

    // 🔹 Pass-by-pointer function
    updatePoint(&p);

    cout << "After update function: ";
    p.display();

    // 🔹 Distance
    cout << "Distance from origin: " << p.distanceFromOrigin() << endl;

    // 🔹 Reset
    resetPoint(&p);

    cout << "After reset: ";
    p.display();

    return 0;
}