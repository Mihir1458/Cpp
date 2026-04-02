#include <iostream>
using namespace std;

class Calculator
{
private:
    float results[50];  
    int index = 0;

public:
    

    int add(int a, int b)
    {
        int res = a + b;
        results[index++] = res;
        return res;
    }

    float add(float a, float b)
    {
        float res = a + b;
        results[index++] = res;
        return res;
    }

    float add(int a, float b)
    {
        float res = a + b;
        results[index++] = res;
        return res;
    }

    float add(float a, int b)
    {
        float res = a + b;
        results[index++] = res;
        return res;
    }

    

    int subtract(int a, int b)
    {
        int res = a - b;
        results[index++] = res;
        return res;
    }

    float multiply(float a, float b)
    {
        float res = a * b;
        results[index++] = res;
        return res;
    }

    float divide(float a, float b)
    {
        if (b == 0)
        {
            cout << "Error: Division by zero!" << endl;
            return 0;
        }
        float res = a / b;
        results[index++] = res;
        return res;
    }

    
    int add(int arr[], int size)
    {
        int sum = 0;
        for (int i = 0; i < size; i++)
        {
            sum += arr[i];
        }
        results[index++] = sum;
        return sum;
    }

    // Display results
    void displayResults()
    {
        cout << "\nStored Results:\n";
        for (int i = 0; i < index; i++)
        {
            cout << results[i] << endl;
        }
    }
};

int main()
{
    Calculator calc;

    cout << "Addition (int): " << calc.add(5, 3) << endl;
    cout << "Addition (float): " << calc.add(2.5f, 3.5f) << endl;
    cout << "Addition (int + float): " << calc.add(5, 2.5f) << endl;

    cout << "Subtraction: " << calc.subtract(10, 4) << endl;
    cout << "Multiplication: " << calc.multiply(2.5f, 4.0f) << endl;
    cout << "Division: " << calc.divide(10.0f, 2.0f) << endl;

    int arr[] = {1, 2, 3, 4};
    cout << "Array Sum: " << calc.add(arr, 4) << endl;

    calc.displayResults();

    return 0;
}