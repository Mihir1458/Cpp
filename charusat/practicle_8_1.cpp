#include <iostream>
using namespace std;
int main()
{
    float n, m;
    cout << "Entre number ";
    cin >> n;
    cout << "Entre divisor number ";
    cin >> m;
    try
    {
        if (m == 0)
        {
            throw(404);
        }
        else
        {
            cout << "Result: " << (n / m) << endl;
        }
    }
    catch (int err)
    {
        cout << "Error: Invalid divisor. Please enter a valid number." << endl;
    }
    return 0;
}