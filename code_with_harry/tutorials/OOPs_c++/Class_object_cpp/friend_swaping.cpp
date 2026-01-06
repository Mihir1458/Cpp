#include<iostream>
using namespace std;
class p;
class q{
    int a;
    friend void swaping(q &,p &);
    
    public:
    void set(int x)
    {
        a=x;
    }
    void display()
    {
        cout<<" the number is :-"<<a<<endl;
    }
};
class p{
    int b;
    friend void swaping(q &,p &);
    public:
    void set(int y)
    {
        b=y;
    }
    void display()
    {
        cout<<" the number is :-"<<b<<endl;
    }
};
void swaping(q &x,p &y)
{
    int temp;
    temp=x.a;
    x.a=y.b;
    y.b=temp;
}
int main()
{
     q e;
    p r;
    e.set(55);
    e.display();
    r.set(5);
    r.display();
    
    swaping(e,r);
    e.display();
    r.display();
return 0;
}