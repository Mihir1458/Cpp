#include <iostream>
#include <algorithm>
using namespace std;
template <typename t>

void max(t arr[],int n)
{
    t max = arr[0];
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    cout << "the maximum element is " << max << endl;
}
template <typename T>
void revse(T arr[],int n)
{
    // int n = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < (n / 2); i++)
    {
        swap(arr[i], arr[n - i - 1]);
    }
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
template <typename X>
void leader(X arr[],int n)
{
    // int n = sizeof(arr) / sizeof(arr[0]);
    int counter = 0;
    for (int i = 1; i < n; i++)
    
    {
        // int arr[counter];
        if (arr[counter] < arr[i])
        {
            
            cout << arr[i] << " ";
            counter += 2;
        }
        else if (arr[counter] == arr[n - 1])
        {
            cout << arr[n - 1] << " ";
        }
        
        
    }
    cout << endl;
}
int main()
{
    
    int arr[] = {16, 17, 4, 7, 3, 5, 2};
     int n = sizeof(arr) / sizeof(arr[0]);
    
    max(arr,n);
    leader(arr,n);
    revse(arr,n);
    

    return 0;
}