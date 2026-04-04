#include <iostream>
using namespace std;

class Calculator
{
private:
    double results[100];
    int index;

public:
    Calculator()
    {
        index = 0;
        cout << "Calculator Started " << endl;
    }

    int add(int a, int b)
    {
        int res = a + b;
        storeResult(res);
        return res;
    }

    float add(float a, float b)
    {
        float res = a + b;
        storeResult(res);
        return res;
    }

    int add(int a, int b, int c)
    {
        int res = a + b + c;
        storeResult(res);
        return res;
    }

    double add(double a, int b)
    {
        double res = a + b;
        storeResult(res);
        return res;
    }

    double add(int a, double b)
    {
        double res = a + b;
        storeResult(res);
        return res;
    }

    void storeResult(double value)
    {
        results[index++] = value;
    }

    void displayResults()
    {

        for (int i = 0; i < index; i++)
        {
            cout << "Result " << i + 1 << ": " << results[i] << endl;
        }
    }
};

int main()
{
    Calculator calc;
    int choice;

    do
    {

        cout << "1. Add two integers\n";
        cout << "2. Add two floats\n";
        cout << "3. Add three integers\n";
        cout << "4. Add double and int\n";
        cout << "5. Add int and double\n";
        cout << "6. Show all results\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        int a, b, c;
        float f1, f2;
        double d;

        switch (choice)
        {
        case 1:
            cout << "Enter two integers: ";
            cin >> a >> b;
            cout << "Result: " << calc.add(a, b) << endl;
            break;

        case 2:
            cout << "Enter two floats: ";
            cin >> f1 >> f2;
            cout << "Result: " << calc.add(f1, f2) << endl;
            break;

        case 3:
            cout << "Enter three integers: ";
            cin >> a >> b >> c;
            cout << "Result: " << calc.add(a, b, c) << endl;
            break;

        case 4:
            cout << "Enter double and int: ";
            cin >> d >> a;
            cout << "Result: " << calc.add(d, a) << endl;
            break;

        case 5:
            cout << "Enter int and double: ";
            cin >> a >> d;
            cout << "Result: " << calc.add(a, d) << endl;
            break;

        case 6:
            calc.displayResults();
            break;

        case 7:
            cout << "Thank you!\n";
            break;

        default:
            cout << "Invalid choice\n";
        }

    } while (choice != 7);

    return 0;
}