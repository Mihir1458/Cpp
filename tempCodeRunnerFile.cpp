#include <iostream>
using namespace std;

// -------- Display Array --------
template <class T>
void display(T arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// -------- Find Maximum --------
template <class T>
T findMax(T arr[], int n)
{
    T max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

// -------- Reverse Array --------
template <class T>
void reverseArray(T arr[], int n)
{
    for (int i = 0; i < n / 2; i++)
    {
        T temp = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = temp;
    }
}

// -------- Leader Elements --------
template <class T>
void leaderElements(T arr[], int n)
{
    T leader = arr[n - 1];
    cout << leader << " ";

    for (int i = n - 2; i >= 0; i--)
    {
        if (arr[i] > leader)
        {
            leader = arr[i];
            cout << leader << " ";
        }
    }
    cout << endl;
}

// -------- Minimum Element --------
template <class T>
T findMin(T arr[], int n)
{
    T min = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < min)
            min = arr[i];
    }
    return min;
}

// -------- Search Element --------
template <class T>
int searchElement(T arr[], int n, T key)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == key)
            return i;
    }
    return -1;
}

// -------- Count Occurrences --------
template <class T>
int countOccurrence(T arr[], int n, T key)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == key)
            count++;
    }
    return count;
}

// -------- MAIN --------
int main()
{
    // Integer Array
    int intArr[] = {16, 17, 4, 3, 5, 2};
    int n1 = 6;

    cout << "Integer Array: ";
    display(intArr, n1);

    cout << "Max: " << findMax(intArr, n1) << endl;

    reverseArray(intArr, n1);
    cout << "Reversed: ";
    display(intArr, n1);

    cout << "Leader Elements: ";
    leaderElements(intArr, n1);

    // Float Array
    float floatArr[] = {2.5, 9.1, 3.3, 7.7};
    int n2 = 4;

    cout << "\nFloat Array: ";
    display(floatArr, n2);

    cout << "Max: " << findMax(floatArr, n2) << endl;

    // Character Array
    char charArr[] = {'a', 'z', 'm', 'b'};
    int n3 = 4;

    cout << "\nChar Array: ";
    display(charArr, n3);

    cout << "Max (ASCII based): " << findMax(charArr, n3) << endl;

    cout << "Leader Elements: ";
    leaderElements(charArr, n3);

    return 0;
}
