#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    cout << "Enter size: ";
    cin >> n;

    /*vector<int> v(n); // this can be also used but in this case vector is fixed size and we cannot add more elements to it.
 Enter size: 5
 Enter elements:
 1
 2
 3
 4
 5
 Array : 0 0 0 0 0 1 2 3 4 5 // we had ireated distaly for 2n times to display all element
 Reversed using reverse function :
 5 4 3 2 1
 Reversed  manually:
 1 2 3 4 5
  */
    vector<int> v;
    cout << "Enter elements:" << endl;
    for (int i = 0; i < n; i++)
    {
        // cin >> v[i]; // this is used when we gave size to vector
        int X;
        cin >> X;
        v.push_back(X);
    }

    cout << "Array : ";
    for (int i = 0; i < n + n; i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;

   reverse(v.begin(), v.end());

    cout << "Reversed using reverse function :  " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;

    cout << "Reversed  manually: " << endl;
    for (int i = 0; i < (n / 2); i++)
    {
        swap(v[i], v[n - i - 1]);
    }
    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;

    return 0;
}