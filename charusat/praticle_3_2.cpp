#include <iostream>

using namespace std;

int recursiveSum(int arr[], int n)
{

    if (n == 0)
        return 0;

    return arr[n - 1] + recursiveSum(arr, n - 1);
}

int iterativeSum(int arr[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];

    return sum;
}

int main()
{
    int n, arr[n];

    cout << "Enter array size: ";
    cin >> n;

    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int recSum = recursiveSum(arr, n);

    int itrSum = iterativeSum(arr, n);

    cout << "\nRecursive Sum = " << recSum << endl;

    cout << "\nIterative Sum = " << itrSum << endl;

    return 0;
}
