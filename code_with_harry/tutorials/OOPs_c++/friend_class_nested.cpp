#include<iostream>
using namespace std;
class calc; //forward declaration
class complex{
    int a,b;
    friend class calc;
    public:
    void set(int x,int y)
    {
        a=x;
        b=y;
    }
    void print()
    {
        cout<<"The complex number is "<<a<<" + "<<b<<"i"<<endl;
    }

};
class calc{
    public:
    int realsum(complex a1,complex b1)
    {
        return (a1.a+b1.a);
    }
    int imagsum(complex a1,complex b1)
    {
        return (a1.b+b1.b);
    }
    int sumcrossreal(complex a1,complex b1)
    {
        return (a1.a+b1.b);
    }
    int sumcrossimag(complex a1,complex b1)
    {
        return (a1.b+b1.a);
    }

};
int main()
{
    complex c1,c2;
    c1.set(3,4);
    c1.print();
    c2.set(5,3);
    c2.print();
    calc calc1;
    cout<<"Real sum: "<<calc1.realsum(c1,c2)<<endl;
    cout<<"Imaginary sum: "<<calc1.imagsum(c1,c2)<<endl;
    cout<<"Cross Real sum: "<<calc1.sumcrossreal(c1,c2)<<endl;
    cout<<"Cross Imaginary sum: "<<calc1.sumcrossimag(c1,c2)<<endl;

    return 0;
}