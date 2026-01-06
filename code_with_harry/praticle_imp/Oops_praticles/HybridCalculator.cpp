#include <iostream>
#include <cmath>
using namespace std;

// -------- Simple Calculator --------
class SimpleCalculator {
protected:
    double a, b;

public:
    void getSimpleInput() {
        cin >> a >> b;
    }

    void showSimpleResult() {
        cout << "Addition: " << a + b << endl;
        cout << "Subtraction: " << a - b << endl;
        cout << "Multiplication: " << a * b << endl;
        cout << "Division: " << a / b << endl;
    }
};

// -------- Scientific Calculator --------
class ScientificCalculator {
protected:
    double x, y;

public:
    void getScientificInput() {
        cin >> x >> y;
    }

    void showScientificResult() {
        cout << "Power (x^y): " << pow(x, y) << endl;
        cout << "Square root of x: " << sqrt(x) << endl;
        cout << "Log(x): " << log(x) << endl;
        cout << "Sin(x): " << sin(x) << endl;
    }
};

// -------- Hybrid Calculator --------
class HybridCalculator : public SimpleCalculator, public ScientificCalculator {
};

// -------- Main --------
int main() {
    HybridCalculator obj;

    cout << "Enter two numbers for Simple Calculator: ";
    obj.getSimpleInput();
    obj.showSimpleResult();

    cout << "\nEnter two numbers for Scientific Calculator: ";
    obj.getScientificInput();
    obj.showScientificResult();

    return 0;
}
