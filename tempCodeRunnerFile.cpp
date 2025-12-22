#include<iostream>
using namespace std;
class b1;
class a1{
    int a;
    friend void swaing(a1 &,b1 &);
    public:
    void get(int m)
    {
        a=m;
    }
    void out()
    {
        cout<<"The value of the first number is :- "<<a<<endl;
    }
};
class b1{
    int b;
    
    friend void swaing(a1 &,b1 &);
    public:
    void get(int n)
    {
        b=n;
    }
    void out()
    {
        cout<<"The value of the first number is :- "<<b<<endl;
    }
};
void swaing(a1 &c, b1 &d)
{
int temp;
temp=c.a;
c.a=d.b;
d.b=temp;
}
int main()
{
     a1 p;  
     b1 k;
    p.get(90);
    p.out();
    k.get(55);
    k.out();
    
    swaing(p,k);
    p.out();
    k.out();
   return 0; 

}