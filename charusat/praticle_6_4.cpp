#include <iostream>
using namespace std;
class base_acc
{
protected:
    string acc_no;
    double current_balance;

public:
    base_acc()
    {
        acc_no = "**";
        current_balance = 0.0;
    }
    base_acc(string no, double balance)
    {
        acc_no = no;
        current_balance = balance;
    }

    void display()
    {
        cout << "Account No: " << acc_no << endl;
        cout << "Current Balance: " << current_balance << endl;
    }
    void withdraw(double amount)
    {
        if (amount > current_balance)
        {
            cout << "Insufficient balance!" << endl;
        }
        else
        {
            current_balance -= amount;
            cout << "Withdrawal successful. New balance: " << current_balance << endl;
        }
    }
    void deposit(double amount)
    {
        current_balance += amount;
        cout << "Deposit successful. New balance: " << current_balance << endl;
    }
    ~base_acc()
    {
        cout << "Base class destructor called" << endl;
    }
};
class saving_acc : public base_acc
{
protected:
    double interest_rate;

public:
    saving_acc()
    {
        interest_rate = 0.0;
    }
    saving_acc(string no, double balance, double rate) : base_acc(no, balance)
    {
        interest_rate = rate;
    }
    void display()
    {
        base_acc::display();
        cout << "Interest Rate: " << interest_rate << "%" << endl;
    }

    ~saving_acc()
    {
        cout << "Saving account destructor called" << endl;
    }
};
class current_acc : public base_acc
{
protected:
    double overdraft_limit;

public:
    current_acc()
    {
        overdraft_limit = 0.0;
    }
    current_acc(string no, double balance, double limit) : base_acc(no, balance)
    {
        overdraft_limit = limit;
    }
    void display()
    {
        base_acc::display();
        cout << "Overdraft Limit: " << overdraft_limit << endl;
    }
    ~current_acc()
    {
        cout << "Current account destructor called" << endl;
    }
};
int main()
{

    int choice;
    while (choice != 3)
    {
        cout << "what type of account you want to create?" << endl;
        cout << " 1.  saving" << endl;
        cout << "2.  current" << endl;
        cout << "3.  exit" << endl;

        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "how many saving account you want to create?";
            int n;
            cin >> n;
            saving_acc sa[n];
            for (int j = 0; j < n; j++)
            {
                string acc_no;
                double balance, rate;
                cout << "account " << j + 1 << ":" << endl;
                cout << "Enter account number: ";
                cin >> acc_no;
                cout << "Enter current balance: ";
                cin >> balance;
                cout << "Enter interest rate for saving account: ";
                cin >> rate;

                saving_acc temp(acc_no, balance, rate);
                sa[j] = temp;
                cout << "\nSaving Account Details:" << endl;
                sa[j].display();
                cout << "------------------------------" << endl;
                int k;
                cout << "If you want to deposit entre '1" << endl;
                cout << "if you want to withdraw enter '2' " << endl;
                cout << "for continue enter '3'" << endl;

                cin >> k;
                if (k == 1)
                {
                    double amount;
                    cout << "Enter the amount you want to deposit: ";
                    cin >> amount;
                    sa[j].deposit(amount);
                }
                else if (k == 2)
                {
                    double amount;
                    cout << "Enter the amount you want to withdraw: ";
                    cin >> amount;
                    sa[j].withdraw(amount);
                }
                else if (k == 3)
                {
                    continue;
                }
                else
                {
                    cout << "Invalid choice!" << endl;
                }
            }
        }
        break;
        case 2:
        {
            cout << "how many current account you want to create?";
            int n;
            cin >> n;
            current_acc ca[n];
            for (int j = 0; j < n; j++)
            {
                string acc_no;
                double balance, limit;
                cout << "account " << j + 1 << ":" << endl;
                cout << "Enter account number: ";
                cin >> acc_no;
                cout << "Enter current balance: ";
                cin >> balance;
                cout << "Enter overdraft limit for current account: ";
                cin >> limit;

                current_acc temp(acc_no, balance, limit);
                ca[j] = temp;

                cout << "\nCurrent Account Details:" << endl;
                ca[j].display();
                cout << "------------------------------" << endl;
                int k;
                cout << "If you want to deposit entre '1' " << endl;
                cout << "if you want to withdraw enter '2' " << endl;
                cout << "for continue enter '3'" << endl;
                cin >> k;
                if (k == 1)
                {
                    double amount;
                    cout << "Enter the amount you want to deposit: ";
                    cin >> amount;
                    ca[j].deposit(amount);
                }
                else if (k == 2)
                {
                    double amount;
                    cout << "Enter the amount you want to withdraw: ";
                    cin >> amount;
                    ca[j].withdraw(amount);
                }
                else if (k == 3)
                {
                    continue;
                }
                else
                {
                    cout << "Invalid choice!" << endl;
                }
            }
        }
        case 3:
        {
            cout << "Exiting..." << endl;
            break;
        }

        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    }

    return 0;
}