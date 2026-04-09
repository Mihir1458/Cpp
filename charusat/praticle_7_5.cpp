#include <iostream>
using namespace std;
class student
{
public:
    virtual void grading() = 0;
};
class UG : public student
{
    int roll;
    string name;
    int marks[3];

public:
    UG() : student()
    {
        roll = 0;
        name = "";
        for (int i = 0; i < 3; i++)
        {
            marks[i] = 0;
        }
    }
    UG(int r, string n, int m1, int m2, int m3) : student()
    {
        roll = r;
        name = n;
        marks[0] = m1;
        marks[1] = m2;
        marks[2] = m3;
    }
    void grading()
    {
        int total = 0;
        for (int i = 0; i < 3; i++)
        {
            total += marks[i];
        }
        float avg = total / 3.0;
        cout << "Name: " << name << endl;
        cout << "Roll No: " << roll << endl;
        if (avg >= 90)
        {
            cout << "Grade 'A' " << "and percentage is " << avg << "%" << endl;
        }
        else if (avg >= 80)
        {
            cout << "Grade 'B' " << "and percentage is " << avg << "%" << endl;
        }
        else if (avg >= 70)
        {
            cout << "Grade 'C' " << "and percentage is " << avg << "%" << endl;
        }
        else if (avg >= 60)
        {
            cout << "Grade 'D' " << "and percentage is " << avg << "%" << endl;
        }
        else
        {
            cout << "Grade 'F' " << "and percentage is " << avg << "%" << endl;
        }
    }
    ~UG()
    {
        cout << "Destructor called for UG student: " << name << endl;
    }
};
class PG : public student
{
    int roll;
    string name;
    int marks[3];

public:
    PG() : student()
    {
        roll = 0;
        name = "";
        for (int i = 0; i < 3; i++)
        {
            marks[i] = 0;
        }
    }
    PG(int r, string n, int m1, int m2, int m3) : student()
    {
        roll = r;
        name = n;
        marks[0] = m1;
        marks[1] = m2;
        marks[2] = m3;
    }
    void grading()
    {
        int total = 0;
        for (int i = 0; i < 3; i++)
        {
            total += marks[i];
        }
        float avg = total / 30.0;
        cout << "Name: " << name << endl;
        cout << "Roll No: " << roll << endl;
        if (avg >= 9)
        {
            cout << "Grade 'O' " << "and CGPA is " << avg << endl;
        }
        else if (avg >= 8)
        {
            cout << "Grade 'A' " << "and CGPA  is " << avg << endl;
        }
        else if (avg >= 7)
        {
            cout << "Grade 'B' " << "and CGPA is " << avg << endl;
        }
        else if (avg >= 6)
        {
            cout << "Grade 'C' " << "and CGPA is " << avg << endl;
        }
        else
        {
            cout << "Grade 'D' " << "and CGPA is " << avg << endl;
        }
    }
    ~PG()
    {
        cout << "Destructor called for PG student: " << name << endl;
    }
};
int main()
{
    UG u1(27, "mihir", 85, 90, 80);
    PG p1(31, "nirbhay", 75, 80, 70);

    cout << "UG Student: " << endl;
    u1.grading();

    cout << "PG Student: " << endl;
    p1.grading();

    return 0;
}