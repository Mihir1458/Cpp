#include <iostream>
using namespace std;
class Enhanced_Account_Tracking_System
{
private:
    string account_number;
    string account_holder_name;
    double balance;
    int transaction_count;
    static int total_accounts;

public:
    Enhanced_Account_Tracking_System()
    {
        account_number = "AC0000";
        account_holder_name = "Default User";
        balance = 0.0;
        transaction_count = 0;
        total_accounts++;
    }
    Enhanced_Account_Tracking_System(string acc_num, string name, double bal)
    {
        account_number = acc_num;
        account_holder_name = name;
        balance = bal;
        transaction_count = 0;
    }
    void transaction_fees(double fee = 20)
    {
        if (fee > 0 && fee <= balance)
        {
            balance -= fee;
            cout << "Transaction fee of $" << fee << " applied." << endl;
        }
        else
        {
            cout << "Invalid fee amount or insufficient funds!" << endl;
        }
    }
    void displayAccountDetails()
    {
        cout << "Account Number: " << account_number << endl;
        cout << "Account Holder Name: " << account_holder_name << endl;
        cout << "Balance:" << balance << endl;
    }
    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            cout << "Deposited: $" << amount << endl;
            transaction_count++;
            transaction_fees(); // Apply transaction fee after deposit
        }
        else
        {
            cout << "Invalid deposit amount!" << endl;
        }
    }
    void withdraw(double amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            cout << "Withdrew: $" << amount << endl;
            transaction_count++;
            transaction_fees(); // Apply transaction fee after deposit
        }
        else
        {
            cout << "Invalid withdrawal amount or insufficient funds!" << endl;
        }
    }
    void transfer(int n, Enhanced_Account_Tracking_System acc[], string target_account_number, double amount)
    {
        for (int i = 0; i < n; i++)
        {
            if (acc[i].account_number == target_account_number)
            {
                if (amount > 0 && amount <= balance)
                {
                    balance -= amount;
                    acc[i].balance += amount;
                    cout << "Transfer successful!" << endl;
                    transaction_count++;
                    transaction_fees(); // Apply transaction fee after deposit
                }
                else
                {
                    cout << "Invalid transfer amount or insufficient funds!" << endl;
                }
                break;
            }
        }
    }
    static int getTotalAccounts()
    {
        return total_accounts;
    }
    int getTransactionCount()
    {
        return transaction_count;
    }
    string getAccountNumber()
    {
        return account_number;
    }
    void add_new_account(Enhanced_Account_Tracking_System acc[])
    {
        string acc_num, name;
        double bal;

        cout << "Enter account number: ";
        cin >> acc_num;
        cout << "Enter account holder name: ";
        cin >> name;
        cout << "Enter initial balance: ";
        cin >> bal;
        if (bal >= 2000)
        {
            acc[total_accounts] = Enhanced_Account_Tracking_System(acc_num, name, bal);
            cout << "Account created successfully!" << endl;
            total_accounts++;
            transaction_count++;
        }
        else
        {
            cout << "Initial balance must be at least $2000!" << endl;
        }
    }
};
int Enhanced_Account_Tracking_System::total_accounts = 0;
int main()
{
    cout << "how many accounts you want to create: ";
    int n;
    cin >> n;
    Enhanced_Account_Tracking_System acc[n];
    int k;
    do
    {
        cout << "*******************************************" << endl;
        cout << "1. Add new account" << endl;
        cout << "2. Add details of existing account" << endl;
        cout << "3. Display details of existing account" << endl;
        cout << "4. Deposit money" << endl;
        cout << "5. Withdraw money" << endl;
        cout << "6. Transfer money" << endl;
        cout << "7. Display total number of accounts" << endl;
        cout << "8. Display total number of transactions" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> k;
        switch (k)
        {
        case 1:
        {
            acc[n].add_new_account(acc);
            n++;
            break;
        }
        case 2:
        {

            for (int i = 0; i < n; i++)
            {
                string acc_num;

                string name;
                double bal;
                cout << "Enter account number: ";
                cin >> acc_num;
                cout << "Enter account holder name: ";
                cin >> name;
                cout << "Enter balance: ";
                cin >> bal;
                acc[i] = Enhanced_Account_Tracking_System(acc_num, name, bal);
                cout << "Account details added successfully!" << endl;
            }
            break;
        }
        case 3:
        {

            for (int i = 0; i < n; i++)
            {

                acc[i].displayAccountDetails();
            }
            cout << Enhanced_Account_Tracking_System::getTotalAccounts() << " accounts are created." << endl;
            break;
        }
        case 4:
        {
            string acc_num;
            double amount;
            cout << "Enter account number: ";
            cin >> acc_num;
            cout << "Enter deposit amount: ";
            cin >> amount;
            for (int i = 0; i < n; i++)
            {
                if (acc[i].getAccountNumber() == acc_num)
                {
                    acc[i].deposit(amount);
                    break;
                }
            }
            break;
        }
        case 5:
        {
            string acc_num;
            double amount;
            cout << "Enter account number: ";
            cin >> acc_num;
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            for (int i = 0; i < n; i++)
            {
                if (acc[i].getAccountNumber() == acc_num)
                {
                    acc[i].withdraw(amount);
                    break;
                }
            }
            break;
        }
        case 6:
        {
            string source_acc_num, target_acc_num;
            double amount;
            cout << "Enter source account number: ";
            cin >> source_acc_num;
            cout << "Enter target account number: ";
            cin >> target_acc_num;
            cout << "Enter transfer amount: ";
            cin >> amount;
            for (int i = 0; i < n; i++)
            {
                if (acc[i].getAccountNumber() == source_acc_num)
                {
                    acc[i].transfer(n, acc, target_acc_num, amount);
                    break;
                }
            }
            break;
        }
        case 7:
            cout << "Total accounts: " << Enhanced_Account_Tracking_System::getTotalAccounts() << endl;
            break;
        case 8:
            for (int i = 0; i < n; i++)
            {
                cout << "Account " << acc[i].getAccountNumber() << " has " << acc[i].getTransactionCount() << " transactions." << endl;
            }
            break;
        case 0:
            cout << "Exiting..." << endl;
        }
    } while (k != 0);
}