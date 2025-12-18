#include<iostream>
using namespace std;
int fib(int a);
int main()
{
    // fib(5)
// fib(4) + fib(3)
// fib(2) + fib(3) + fib(2) + fib(3
    int a=0,ans;
    cout<<"ENtre number for which do want to find the fibonacci:- ";
    cin>>a;
    ans=fib(a);
    cout<<ans;
    return 0;
}
int fib(int a){
    if(a<=1)
    {
        return 1;
    }
    return fib(a-1)+fib(a-2);
    
     
}
