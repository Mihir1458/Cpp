#include <iostream>
using namespace std;

int main()
{
    int n, m;

    cout << "Enter size of first array: ";
    cin >> n;

    cout << "Enter size of second array: ";
    cin >> m;

    int *A = new int[n];
    int *B = new int[m];

    cout << "Enter elements of first sorted array:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
    }

    cout << "Enter elements of second sorted array:\n";
    for (int i = 0; i < m; i++)
    {
        cin >> B[i];
    }
    int newsize = n + m;
    int *C = new int[newsize];

    int i = 0, j = 0, k = 0;

      while (i < n)
    {
        C[k++] = A[i++];
    }

    while (j < m)
    {
        C[k++] = B[j++];
    }
    // Sort the merged array
    for (int i = 0; i < newsize - 1; i++)
    {
        for (int j = 0; j < newsize - i - 1; j++)
        {
            if (C[j] > C[j + 1])
            {
                swap(C[j], C[j + 1]);
            }
        }
    }

    cout << "Merged Array: ";
    for (int i = 0; i < newsize; i++)
    {
        cout << C[i] << " ";
    }
    cout << endl;

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}