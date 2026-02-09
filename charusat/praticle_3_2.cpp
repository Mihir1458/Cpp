#include <iostream>
#include <chrono>   // For execution time measurement
using namespace std;
using namespace std::chrono;

// ================================
// Recursive Function
// ================================
int recursiveSum(int arr[], int n)
{
    // Base Case
    if (n == 0)
        return 0;

    // Recursive Case
    return arr[n - 1] + recursiveSum(arr, n - 1);
}

// ================================
// Iterative Function
// ================================
int iterativeSum(int arr[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];

    return sum;
}

// ================================
// Main Function
// ================================
int main()
{
    int n;

    cout << "Enter array size: ";
    cin >> n;

    // Dynamic Array Allocation
    int *arr = new int[n];

    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    // ----------------------------
    // Recursive Execution Time
    // ----------------------------
    auto start1 = high_resolution_clock::now();
    int recSum = recursiveSum(arr, n);
    auto end1 = high_resolution_clock::now();

    auto recTime = duration_cast<nanoseconds>(end1 - start1);

    // ----------------------------
    // Iterative Execution Time
    // ----------------------------
    auto start2 = high_resolution_clock::now();
    int itrSum = iterativeSum(arr, n);
    auto end2 = high_resolution_clock::now();

    auto itrTime = duration_cast<nanoseconds>(end2 - start2);

    // ----------------------------
    // Output Results
    // ----------------------------
    cout << "\nRecursive Sum = " << recSum << endl;
    cout << "Recursive Time = " << recTime.count() << " ns\n";

    cout << "\nIterative Sum = " << itrSum << endl;
    cout << "Iterative Time = " << itrTime.count() << " ns\n";

    // Free Memory
    delete[] arr;

    return 0;
}
