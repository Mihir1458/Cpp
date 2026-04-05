#include <iostream>
using namespace std;

int main()
{
    string n;
    int k;

    cout << "Enter number (as string): ";
    cin >> n;

    cout << "Enter k: ";
    cin >> k;

    long long sum = 0;

    for (int i = 0; i < n.size(); i++)
    {
        sum = sum + (n[i] - '0');
    }

    sum = sum * k;

    while (sum > 9) // recursive also can be used
    {
        long long tempSum = 0;
        while (sum > 0)
        {
            tempSum += sum % 10;
            sum /= 10;
        }
        sum = tempSum;
    }
    cout << "Super Digit: " << sum;

    return 0;
}