#include <iostream>
using namespace std;
class dynamicarray
{
    int *arr;
    int size;

public:
    dynamicarray()
    {
        arr = nullptr;
        size = 0;
    }
    void insternew(int val)
    {

        int *newarray = new int[size + 1];
        for (int i = 0; i < size; i++)
        {
            newarray[i] = arr[i];
        }
        newarray[size] = val;
        delete[] arr;
        arr = newarray;
        size++;
    }
    void remove(int p)
    {
        if (size == 0)
        {
            cout << "Array is empty\n";
            return;
        }
        if (p < 0 || p >= size)
        {
            cout << "Invalid position\n";
            return;
        }
        int *newarray = new int[size - 1];
        for (int i = 0, j = 0; i < size; i++)
        {
            if (i != p)
            {
                newarray[j++] = arr[i];
            }
        }
        delete[] arr;
        arr = newarray;
        size--;
    }
    void insterat(int p, int val)
    {
        if (p < 0 || p > size)
        {
            cout << "Invalid position\n";
            return;
        }
        int *newarray = new int[size + 1];
        for (int i = 0, j = 0; i < size + 1; i++)
        {
            if (i == p)
            {
                newarray[i] = val;
            }
            else
            {
                newarray[i] = arr[j++];
            }
        }
        delete[] arr;
        arr = newarray;
        size++;
    }
    void serch(int val)
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i] == val)
            {
                cout << "number found at position: " << i << endl;
                return;
            }
        }
        cout << "number not found\n";
    }
    void count(int val)
    {
        int count = 0;
        for (int i = 0; i < size; i++)
        {
            if (arr[i] == val)
            {
                count++;
            }
        }
        cout << "Count of " << val << ": " << count << endl;
    }
    void display()
    {
        if (size == 0)
        {
            cout << "Array is empty\n";
            return;
        }
        cout << "Array: ";
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};
int main()
{
    dynamicarray c1;

    for (int i = 1; i <= 5; i++)
    {
        c1.insternew(i * 10);
    }
    c1.display();
    c1.insternew(20);
    c1.display();
    c1.remove(2);
    c1.display();
    c1.insterat(2, 30);
    c1.display();
    c1.serch(30);
    c1.count(20);
    return 0;
}