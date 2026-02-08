#include <iostream>
using namespace std;
class digital_saving_account
{
    string Customer_name, Unique_account_ID;
    float Current_balance;

public:
    digital_saving_account()
    {
        cout << endl
             << "Default Constructor Called!" << endl;
        Customer_name = "-------";
        Unique_account_ID = "******";
        Current_balance = 0;
    }
    digital_saving_account(string name, string id, float balance)
    {
        cout << endl
             << "Parameterized Constructor Called!" << endl;
        Customer_name = name;
        Unique_account_ID = id;
        Current_balance = balance;
    }
    void add_acc();
    void deposit(float amount);
    void withdraw(float amount);
    void display();
};
void digital_saving_account::add_acc()
{
    cout << "Enter Customer Name: ";
    cin >> Customer_name;
    cout << "Enter Unique Account ID: ";
    cin >> Unique_account_ID;
    cout << "Enter Current Balance: ";
    cin >> Current_balance;
}
void digital_saving_account::display()
{
    cout << "Customer Name: " << Customer_name << endl;
    cout << "Unique Account ID: " << Unique_account_ID << endl;
    cout << "Current Balance: " << Current_balance << endl;
}
void digital_saving_account::deposit(float amount)
{
    Current_balance += amount;
}
void digital_saving_account::withdraw(float amount)
{
    if (amount <= Current_balance)
    {
        Current_balance -= amount;
    }
    else
    {
        cout << "Insufficient Balance!" << endl;
    }
}
int main()
{
    int k;
    cout << "Enter Number of Accounts: ";
    cin >> k;
    digital_saving_account account[k];

    cout << "1. Add Account 2. Display Account 3. Deposit 4. Withdraw 5. Exit ";
    int n;
    cin >> n;
    while (n != 5)
    {
        switch (n)
        {
        case 1:
            account[0].add_acc();
            break;
        case 2:
            account[0].display();
            break;
        case 3:
            float amount;
            cout << "Enter Amount to Deposit: ";
            cin >> amount;
            account[0].deposit(amount);
            break;
        case 4:
            cout << "Enter Amount to Withdraw: ";
            cin >> amount;
            account[0].withdraw(amount);
            break;
        }
        cout << "1. Add Account 2. Display Account 3. Deposit 4. Withdraw 5. Exit ";
        cin >> n;
    }
}