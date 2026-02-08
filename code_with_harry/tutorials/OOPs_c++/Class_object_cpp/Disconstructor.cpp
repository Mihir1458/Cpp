#include <iostream>
using namespace std;
int count = 0;
class dis
{
public:
    dis()
    {
        count++;
        cout << "the Constructpr is called and the number is :- " << count << endl;
    }
    ~dis()
    {
        cout << "the disConstructor is called and the number is :- " << count << endl;
        count--;
    }
};
int main()
{
    cout << "We are in th main function" << endl;

    dis n1;
    {
        cout << "We had entres the n1 objects" << endl;
        cout << "Now we are creating two more objects" << endl;
        dis n2, n3;
        cout << "We are exting  the n1 objects" << endl;
    }
    cout << "back to main" << endl;
    return 0;
}
