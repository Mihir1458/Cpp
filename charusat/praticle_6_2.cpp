#include <iostream>
using namespace std;
class Person
{
private:
    string name;
    int age;

public:
    Person()
    {
        name = "";
        age = 0;
    }
    Person(string n, int a)
    {
        name = n;
        age = a;
    }
    void display()
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }
};
class Employee : public Person
{
private:
    int empId;

public:
    Employee()
    {
        empId = 0;
    }
    Employee(string n, int a, int id) : Person(n, a)
    {
        empId = id;
    }
    void display()
    {
        Person::display();
        cout << "Employee ID: " << empId << endl;
    }
};
class Manager : public Employee
{
private:
    string department;

public:
    Manager()
    {
        department = "";
    }
    Manager(string n, int a, int id, string dept) : Employee(n, a, id)
    {
        department = dept;
    }
    void display()
    {
        //  cout<<"Name: "<<name<<endl; privtae members can not accesed in derived class if needed then use proctected
        // cout<<"Age: "<<age<<endl;
        Employee::display();

        cout << "Department: " << department << endl;
    }
};
int main()
{
    Manager m("Mihir", 35, 27, "HR");
    Manager m1[3];
    for (int i = 0; i < 3; i++)
    {
        string name, dept;
        int age, id;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter age: ";
        cin >> age;
        cout << "Enter employee ID: ";
        cin >> id;
        cout << "Enter department: ";
        cin >> dept;
        Manager temp(name, age, id, dept);
        m1[i] = temp;
    }
    m.display();
    for (int i = 0; i < 3; i++)
    {
        m1[i].display();
    }
    return 0;
}