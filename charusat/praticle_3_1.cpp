#include <iostream>
using namespace std;
class salary_bonus
{
    string name;
    double salary;
    double bonus;

public:
    salary_bonus()
    {
        name = "Unknown";
        salary = 0;
        bonus = 0;
    }
    salary_bonus(string n, double s, double b = 2000)
    {
        name = n;
        salary = s;
        bonus = b;
    }
    void display()
    {
        cout << "\nEmployee Name : " << name;
        cout << "\nBasic Salary  : " << salary;
        cout << "\nBonus         : " << bonus;
        cout << "\nTotal Salary  : " << total_salary();
        cout << "\nGrade         : " << grade_salary();
        cout << "\n---------------------------" << endl;
    }
    inline double total_salary()
    {
        return salary + bonus;
    }

    void update_bonus(double new_bonus)
    {
        bonus = new_bonus;
    }
    char grade_salary()
    {
        if (total_salary() > 50000)
        {

            return 'A';
        }
        else if (total_salary() > 30000)
        {
            return 'B';
        }
        else
        {
            return 'C';
        }
    }
};
int main()
{
    int n;
    cout << "Enter number of employees: ";
    cin >> n;
    salary_bonus employees[n];

    int k;
    do
    {
        cout << "1. Add new Employee and  Details" << endl;
        cout << "2. Display Employee Details" << endl;
        cout << "3. Update Employee Bonus" << endl;
        cout << "4. Add  details of employee" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> k;
        switch (k)
        {
        case 1:
        {
            string name;
            double salary, bonus;
            cout << "Enter details for new Employee:" << endl;
            cout << "Name: ";
            cin >> name;
            cout << "Basic Salary: ";
            cin >> salary;
            cout << "Bonus (default is 2000): ";
            cin >> bonus;
            employees[n] = salary_bonus(name, salary, bonus);
            n++;
        }
        break;
        case 2:
        {
            cout << "\nEmployee Details:\n";
            for (int i = 0; i < n; i++)
            {
                employees[i].display();
            }
        }
        break;
        case 3:
        {
            int index;
            double new_bonus;
            cout << "Enter index of employee to update bonus: ";
            cin >> index;
            if (index >= 1 && index <= n)
            {
                cout << "Enter new bonus: ";
                cin >> new_bonus;
                employees[index - 1].update_bonus(new_bonus);
                cout << "Bonus updated successfully." << endl;
            }
        }
        break;
        case 4:
        {
            string name;
            double salary, bonus;
            int i;
            cout << "Enter index of employee to add details (1 to " << n << "): ";
            cin >> i;
            if (i < 1 || i > n)
            {
                cout << "Invalid index!" << endl;
                break;
            }
            cout << "Enter details for Employee " << i << ":" << endl;
            cout << "Name: ";
            cin >> name;
            cout << "Basic Salary: ";
            cin >> salary;
            cout << "Bonus (default is 2000): ";
            cin >> bonus;
            employees[i - 1] = salary_bonus(name, salary, bonus);
        }
        break;
        case 5:
            cout << "Exiting the program. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (k != 5);
}