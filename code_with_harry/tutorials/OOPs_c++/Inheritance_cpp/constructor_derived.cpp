#include<iostream>
using namespace std;
/*
Case1:
class B: public A{
   // Order of execution of constructor -> first A() then B()
};

Case2:
class A: public B, public C{
    // Order of execution of constructor -> B() then C() and A()
};

Case3:
class A: public B, virtual public C{
    // Order of execution of constructor -> C() then B() and A()
};

*/

class base1
{
    int std1;
    public:
     base1(int bq)
    {
        std1 = bq;
        cout<<"constructor 1 called"<<endl;
    }
    void show()
    {
        
        cout<<"The value of base1 is "<<std1<<endl;
    }
};
class base2
{
    int std2;
    public:
    base2(int bq)
    {
        std2 = bq;
        cout<<"constructor 2 called"<<endl;
    }
    void show2()
    {
        cout<<"The value of base2 is "<<std2<<endl;
    }
};
class derived : public base2, public  base1
{
    int std3;
    public:
    derived(int a, int b, int c):base2(b), base1(a) // Constructor of derived class
    {
    
            std3 = c;
            cout<<"constructor 3 called"<<endl;
        }
        void show3()
    {
        cout<<"The value of base3 is "<<std3<<endl;
    }
            
};
int main()
{
    derived harry(1,2,3);
    harry.show();
    harry.show2();
    harry.show3();
    return 0;
} 