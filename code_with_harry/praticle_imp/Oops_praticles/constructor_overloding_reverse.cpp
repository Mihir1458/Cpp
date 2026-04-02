#include <iostream>
using namespace std;

class ArrayReverse {
public:

    // Constructor for integer array
    ArrayReverse(int arr[], int size) {
        cout << "\nReversed Integer Array: ";
        reverseArray(arr, size);
        printArray(arr, size);
    }

    // Constructor for float array
    ArrayReverse(float arr[], int size) {
        cout << "\nReversed Float Array: ";
        reverseArray(arr, size);
        printArray(arr, size);
    }

    // Constructor for character array
    ArrayReverse(char arr[], int size) {
        cout << "\nReversed Character Array: ";
        reverseArray(arr, size);
        printArray(arr, size);
    }

    // Constructor for string
    ArrayReverse(string str) {
        cout << "\nReversed String: ";
        int start = 0, end = str.length() - 1;

        while(start < end) {
            char temp = str[start];
            str[start] = str[end];
            str[end] = temp;
            start++;
            end--;
        }

        cout << str;
    }

private:

    // Generic reverse logic (manual swap)
    template <typename T>
    void reverseArray(T arr[], int size) {
        int start = 0, end = size - 1;

        while(start < end) {
            T temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;

            start++;
            end--;
        }
    }

    // Generic print function
    template <typename T>
    void printArray(T arr[], int size) {
        for(int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
    }
};

int main() {
    int intArr[] = {1, 2, 3, 4, 5};
    float floatArr[] = {1.1, 2.2, 3.3};
    char charArr[] = {'A', 'B', 'C', 'D'};
    string str = "H E L L O";

    ArrayReverse obj1(intArr, 5);
    ArrayReverse obj2(floatArr, 3);
    ArrayReverse obj3(charArr, 4);
    ArrayReverse obj4(str);

    return 0;
}