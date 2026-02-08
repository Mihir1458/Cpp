#include <iostream>
using namespace std;
class Inventory_Management_System
{
    string Unique_item_ID;
    string Item_name;
    float Price;
    int Quantity_in_stock;

public:
    Inventory_Management_System()
    {
        Unique_item_ID = "*******";
        Item_name = "-------";
        Price = 0;
        Quantity_in_stock = 0;
    }
    Inventory_Management_System(string id, string name, float price, int quantity)
    {
        Unique_item_ID = id;
        Item_name = name;
        Price = price;
        Quantity_in_stock = quantity;
    }
    void add_stock();
    void sell_stock();
    void total_stock(int n, Inventory_Management_System I[]);
    void display();
};
void Inventory_Management_System::add_stock()
{
    int quantity;
    cout << "Enter Quantity to Add: ";
    cin >> quantity;

    Quantity_in_stock += quantity;
}
void Inventory_Management_System::sell_stock()
{
    int quantity;
    cout << "Enter Quantity to Sell: ";
    cin >> quantity;
    if (quantity <= Quantity_in_stock)
    {
        Quantity_in_stock -= quantity;
    }
    else
    {
        cout << "Insufficient Stock!" << endl;
    }
}
void Inventory_Management_System::total_stock(int n, Inventory_Management_System I[])
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        cout << "Item " << i + 1 << ": ";

        sum = sum + I[i].Quantity_in_stock;
    }
    cout << "Total Stock Count: " << sum << endl;
}
void Inventory_Management_System::display()
{
    cout << "*********************************************" << endl;
    cout << "Unique Item ID: " << Unique_item_ID << endl;
    cout << "Item Name: " << Item_name << endl;
    cout << "Price: " << Price << endl;
    cout << "Quantity in Stock: " << Quantity_in_stock << endl;
}
int main()
{
    /* Inventory_Management_System I[3]={
         Inventory_Management_System("12ABC", "Laptop", 90.12, 10),
         Inventory_Management_System(),
         Inventory_Management_System("EF346", "Mouse", 29, 50)
     };
     for(int i=0; i<3; i++)
     {
         I[i].display();
         cout << endl;
     }*/
    int n;
    cout << "How many items do you want to manage? ";
    cin >> n;
    Inventory_Management_System I[n];
    int choice;
    do
    {
        cout << "Items created successfully!" << endl;
        cout << "1. Add details of an item" << endl;
        cout << "2. Sell Stock" << endl;
        cout << "3. Display Inventory" << endl;
        cout << "4. Total Stock Count" << endl;
        cout << "5. Add Stock to an existing item" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            string id, name;
            float price;
            int quantity, ix;
            cout << "Enter Index of Item: ";
            cin >> ix;
            cout << "Enter Unique Item ID: ";
            cin >> id;
            cout << "Enter Item Name: ";
            cin >> name;
            cout << "Enter Price: ";
            cin >> price;
            cout << "Enter Quantity in Stock: ";
            cin >> quantity;
            if (ix >= 0 && ix < n)
                I[ix] = Inventory_Management_System(id, name, price, quantity);
            else
                cout << "Invalid index!" << endl;

            break;
        }
        case 2:
            cout << "Enter index of item to sell stock: ";
            int j;
            cin >> j;
            if (j >= 0 && j < n)
                I[j].sell_stock();
            else
                cout << "Invalid index!" << endl;
            break;
        case 3:
            for (int i = 0; i < n; i++)
            {
                I[i].display();
                cout << endl;
            }
            break;
        case 4:
            I[n - 1].total_stock(n, I);
            break;
        case 5:
            cout << "Enter index of item to add stock: ";
            int i;
            cin >> i;
            if (i >= 0 && i <= n)
            {
                I[i].add_stock();
            }
            else
            {
                cout << "Invalid index!" << endl;
            }
            break;
        case 6:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 5);

    return 0;
}