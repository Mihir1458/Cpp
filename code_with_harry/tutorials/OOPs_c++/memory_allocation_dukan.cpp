#include <iostream>
#include <string>
using namespace std;
class store
{
    int item[100];
    int item_price[100];
    string item_name[100];
    int count;

public:
    void intcount()
    {
        count = 0;
    }
    void set_item();
    void get_item();
};
void store::set_item()
{
    cout << "Enter item number: ";
    cin >> item[count];
    cout << "Enter item price: ";
    cin >> item_price[count];
    cout << "Enter item name: ";
    cin >> item_name[count];
    count++;
}
void store::get_item()
{
    for (int i = 0; i < count; i++)
    {
        cout << "Item number: " << item[i] << endl;
        cout << "Item price: " << item_price[i] << endl;
        cout << "Item name: " << item_name[i] << endl;
    }
}
int main()
{
    int k;
    cout << "How many items do you want to add? ";
    cin >> k;
    store s;
    s.intcount();
    for (int i = 0; i < k; i++)
    {
        s.set_item();
    }
    cout << "You have added following items: " << endl;

    s.get_item();

    return 0;
}