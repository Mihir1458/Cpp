#include<iostream>
#include<cstring>
using namespace std;
/*
student --> inheritance
student --> test
student --> sports
test --> result
sports --> result
*/
class student
{
    protected:
    int roll_no;
    char name[20];
    public:
    void set_roll(int r)
    {
        roll_no = r;
    }
    void set_name(char n[])
    {
        cout<<"Entre name :-";
        cin>>n;
        strcpy(name, n);
    }
};
class test : public virtual student{
    protected:
    float maths,physics;
    public:
    void set_marks(float m, float p)
    {
        maths = m;
        physics = p;
    }
    void get_marks()
    {
        cout<<"Maths: "<<maths<<endl;
        cout<<"Physics: "<<physics<<endl;
    }
};
class sports : public virtual student{
    protected:
    float score;
    public:
    void set_score(float s)
    {
        score = s;
    }
};
class blood : public virtual student{
    protected:
    char bgroup[5];
    public:
    void set_bgroup(char bg[])
    {
        cout<<"Enter blood group:-";
        cin>>bg;
        strcpy(bgroup, bg);
    }
};
class result : public test, public sports, public blood{
    float total;
    public:
    void display()
    {
        total = maths + physics + score;
        cout<<"Name: "<<name<<endl;
        cout<<"Roll No: "<<roll_no<<endl;
        cout<<"Blood Group: "<<bgroup<<endl;
        get_marks();
        cout<<"Sports Score: "<<score<<endl;
        cout<<"Total Marks: "<<total<<endl;
    }
};
int main()
{
    result r;
    char name[20], bg[5];
    r.set_name(name);
    r.set_roll(101);
    r.set_bgroup(bg);
    r.set_marks(95.5, 89.5);
    r.set_score(9.5);
    r.display();
    return 0;
}