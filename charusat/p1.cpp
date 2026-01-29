#include <iostream>

class account
{
private: // Data Member
    std::string user_id;
    double balance;
    std::string name;

public: // Member Function
    void input()
    {
        std::cout << "\n Enter Userid: ";
        std::cin >> user_id;
        std::cout << " \n Enter Balance: ";
        std::cin >> balance;
        std::cout << "\n Enter Name: ";
        std::cin >> name;
    }
    void output()
    {
        std::cout << "\n Enter Userid: " << user_id;
        std::cout << " \n Enter Balance: " << balance;
        std::cout << "\n Enter Name: " << name;
    }
    void chkBalance()
    {

        std::cout << "\n Your Balance is: " << balance << std::endl;
    }
    void MoneyTran()
    {
        float amount;
        std::cout << "\n how much Trancfer want to money? :";
        std::cin >> amount;
        balance -= amount;
        std::cout << amount << "\n Money Trancfer your account " << std::endl;
    }
    void MoneyDepo()
    {
        float amount;
        std::cout << "\n how much deposit want to money? :";
        std::cin >> amount;
        balance += amount;
        std::cout << amount << "\n Money Deposit your account " << std::endl;
    }
};

int main()
{
    account MIHIR;
    MIHIR.input();
    MIHIR.output();
    MIHIR.MoneyDepo();
    MIHIR.output();
    return 0;
}